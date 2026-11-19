import http from 'node:http';
import net from 'node:net';
import fs from 'node:fs/promises';
import fsSync from 'node:fs';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
import {WebSocketServer} from 'ws';
import {TelnetCodec} from './telnet.js';
import {spawn} from 'node:child_process';
import crypto from 'node:crypto';
import {AdminJobState} from './admin_jobs.js';
import {loadBridgeSecret,realIpLine,scrubRealIp} from './real_ip.js';
import {startDirectListener} from './direct.js';

const __dirname=path.dirname(fileURLToPath(import.meta.url));
const ROOT=path.resolve(__dirname,'..');
const WEB=path.join(ROOT,'web');
const UPSTREAM=path.resolve(process.env.ES2_REPO || path.join(ROOT,'source','upstream'));
const MUDLIB=path.join(UPSTREAM,'mudlib');
const BUILD_VERSION=(()=>{try{return fsSync.readFileSync(path.join(ROOT,'VERSION'),'utf8').trim()}catch{return 'unknown'}})();
const CATALOG=path.join(ROOT,'catalog','generated');
const HOST=process.env.HOST||'127.0.0.1';
const PORT=Number(process.env.PORT||8080);
const MUD_HOST=process.env.MUD_HOST||'127.0.0.1';
const MUD_PORT=Number(process.env.MUD_PORT||4000);
const MAX_SESSIONS=Math.max(1,Number(process.env.MAX_SESSIONS||200));
const TCP_CONNECT_TIMEOUT_MS=Math.max(1000,Number(process.env.TCP_CONNECT_TIMEOUT_MS||10000));
const WS_MAX_PAYLOAD_BYTES=Math.max(1024,Number(process.env.WS_MAX_PAYLOAD_BYTES||65536));
const WS_MAX_BUFFERED_BYTES=Math.max(65536,Number(process.env.WS_MAX_BUFFERED_BYTES||1048576));
const HEARTBEAT_MS=Math.max(5000,Number(process.env.HEARTBEAT_MS||30000));
const bridgeStats={startedAt:Date.now(),accepted:0,rejectedCapacity:0,tcpErrors:0,wsErrors:0,peakSessions:0};
const adminJobs=new AdminJobState();
const mime={'.html':'text/html; charset=utf-8','.js':'text/javascript; charset=utf-8','.css':'text/css; charset=utf-8','.json':'application/json; charset=utf-8','.c':'text/plain; charset=utf-8','.h':'text/plain; charset=utf-8','.woff2':'font/woff2','.txt':'text/plain; charset=utf-8','.md':'text/plain; charset=utf-8'};


// 經過反向代理或 Tunnel（Caddy、cloudflared）轉送的請求，來源看起來也是本機，
// 但會帶轉送標頭；這種請求一律視為外部連線，管理功能不開放。
const PROXY_HEADERS=['x-forwarded-for','forwarded','x-real-ip','cf-connecting-ip','cf-ray'];
function isLocal(req){
  if(PROXY_HEADERS.some(h=>req.headers[h]!==undefined))return false;
  return ['127.0.0.1','::1','::ffff:127.0.0.1'].includes(req.socket.remoteAddress||'');
}
function runProcess(cmd,args,{cwd=ROOT,timeout=120000}={}){
  return new Promise((resolve)=>{
    const p=spawn(cmd,args,{cwd,stdio:['ignore','pipe','pipe']});
    let stdout='',stderr='',killed=false;
    const cap=s=>s.length>200000?s.slice(-200000):s;
    p.stdout.on('data',d=>stdout=cap(stdout+d));
    p.stderr.on('data',d=>stderr=cap(stderr+d));
    const timer=setTimeout(()=>{killed=true;p.kill('SIGKILL')},timeout);
    p.on('close',code=>{clearTimeout(timer);resolve({ok:code===0&&!killed,code,stdout,stderr,killed})});
  });
}

function send(res,code,body,type='text/plain; charset=utf-8'){res.writeHead(code,{'content-type':type,'cache-control':'no-store'});res.end(body)}
function safeWithin(base,rel){const out=path.resolve(base,(rel||'').replace(/^\/+/,''));if(out!==base&&!out.startsWith(base+path.sep))throw new Error('path rejected');return out}
async function bodyText(req){let s='';for await(const c of req){s+=c;if(s.length>2000000)throw new Error('body too large')}return s}

const server=http.createServer(async(req,res)=>{
  try{
    const u=new URL(req.url,'http://localhost');


    if(u.pathname==='/api/version'){
      return send(res,200,JSON.stringify({version:BUILD_VERSION,projectRoot:ROOT,mudHost:MUD_HOST,mudPort:MUD_PORT},null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/health'){
      return send(res,200,JSON.stringify({ok:true,bridge:{host:HOST,port:PORT},mud:{host:MUD_HOST,port:MUD_PORT},sessions:sessions?.size??0,connected:[...(sessions?.values?.()||[])].filter(x=>x.tcpConnected).length,maxSessions:MAX_SESSIONS,peakSessions:bridgeStats.peakSessions},null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/runtime-probe'&&req.method==='POST'){
      if(!isLocal(req))return send(res,403,'localhost only');
      const x=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','runtime_probe.py'),'--host',MUD_HOST,'--port',String(MUD_PORT)],{timeout:15000});
      return send(res,x.ok?200:503,x.stdout||x.stderr,'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/runtime-readiness'){
      if(!isLocal(req))return send(res,403,'localhost only');
      const x=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','runtime_readiness.py'),UPSTREAM,'--host',MUD_HOST,'--port',String(MUD_PORT)],{timeout:15000});
      return send(res,x.ok?200:500,x.stdout||x.stderr,'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/admin/verify-source'){
      if(!isLocal(req))return send(res,403,'localhost only');
      const x=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','verify_source.py'),UPSTREAM],{timeout:30000});
      return send(res,x.ok?200:409,JSON.stringify(x,null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/admin/jobs'){
      if(!isLocal(req))return send(res,403,'localhost only');
      return send(res,200,JSON.stringify(adminJobs.snapshot(),null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/admin/reindex'&&req.method==='POST'){
      if(!isLocal(req))return send(res,403,'localhost only');
      let job;
      try{job=adminJobs.start('reindex',{requestedBy:req.socket.remoteAddress||''})}
      catch(e){
        if(e.code==='JOB_BUSY')return send(res,409,JSON.stringify({ok:false,error:'reindex already running',job:e.job},null,2),'application/json; charset=utf-8');
        throw e;
      }
      try{
        adminJobs.stage(job,'verify_source');
        const verify=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','verify_source.py'),UPSTREAM],{timeout:30000});
        if(!verify.ok){
          adminJobs.finish(job,false,{stage:'verify_source',verify});
          return send(res,409,JSON.stringify({ok:false,job,verify},null,2),'application/json; charset=utf-8');
        }
        adminJobs.stage(job,'build_catalog');
        const build=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','build_catalog.py'),UPSTREAM,'-o',CATALOG],{timeout:120000});
        adminJobs.finish(job,build.ok,{stage:'build_catalog',verify,build});
        return send(res,build.ok?200:500,JSON.stringify({ok:build.ok,job,verify,build},null,2),'application/json; charset=utf-8');
      }catch(e){
        adminJobs.finish(job,false,{stage:'exception',error:e.message});
        throw e;
      }
    }
    if(u.pathname==='/api/admin/backups'){
      if(!isLocal(req))return send(res,403,'localhost only');
      const x=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','backup_ops.py'),ROOT,'list'],{timeout:15000});
      return send(res,x.ok?200:500,x.stdout||x.stderr,'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/admin/backup-diff'){
      if(!isLocal(req))return send(res,403,'localhost only');
      const backup=u.searchParams.get('backup')||'',current=u.searchParams.get('current')||'';
      if(!backup||!current)return send(res,400,'backup and current required');
      const x=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','backup_ops.py'),ROOT,'diff',backup,current],{timeout:15000});
      return send(res,x.ok?200:400,x.stdout||x.stderr,'text/plain; charset=utf-8');
    }
    if(u.pathname==='/api/admin/restore'&&req.method==='POST'){
      if(!isLocal(req))return send(res,403,'localhost only');
      const data=JSON.parse(await bodyText(req)||'{}');
      if(!data.backup||!data.current)return send(res,400,'backup and current required');
      const verify=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','verify_source.py'),UPSTREAM],{timeout:30000});
      if(!verify.ok)return send(res,409,JSON.stringify({ok:false,stage:'verify_source',verify},null,2),'application/json; charset=utf-8');
      const x=await runProcess(process.env.PYTHON||'python',[path.join(ROOT,'tools','backup_ops.py'),ROOT,'restore',data.backup,data.current],{timeout:15000});
      return send(res,x.ok?200:400,x.stdout||x.stderr,'application/json; charset=utf-8');
    }

    if(u.pathname==='/api/status'){
      const sourceOK=fsSync.existsSync(path.join(MUDLIB,'std','char.c'))&&fsSync.existsSync(path.join(MUDLIB,'feature','char','combat.c'));
      let catalog=null;try{catalog=JSON.parse(await fs.readFile(path.join(CATALOG,'manifest.json'),'utf8'))}catch{}
      return send(res,200,JSON.stringify({sourceOK,upstream:UPSTREAM,mudHost:MUD_HOST,mudPort:MUD_PORT,catalog},null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/online-count'){
      const connected=[...sessions.values()].filter(s=>s.tcpConnected).length;
      return send(res,200,JSON.stringify({count:connected,connecting:sessions.size-connected,capacity:MAX_SESSIONS},null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/multiplayer-health'){
      const connected=[...sessions.values()].filter(s=>s.tcpConnected).length;
      return send(res,200,JSON.stringify({
        ok:true,
        uptimeSeconds:Math.floor((Date.now()-bridgeStats.startedAt)/1000),
        sessions:{active:sessions.size,connected,connecting:sessions.size-connected,capacity:MAX_SESSIONS,peak:bridgeStats.peakSessions},
        totals:{accepted:bridgeStats.accepted,rejectedCapacity:bridgeStats.rejectedCapacity,tcpErrors:bridgeStats.tcpErrors,wsErrors:bridgeStats.wsErrors},
        limits:{websocketPayloadBytes:WS_MAX_PAYLOAD_BYTES,slowClientBufferedBytes:WS_MAX_BUFFERED_BYTES,heartbeatMs:HEARTBEAT_MS}
      },null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/sessions'){
      if(!isLocal(req))return send(res,403,'localhost only');
      return send(res,200,JSON.stringify({count:sessions.size,capacity:MAX_SESSIONS,sessions:[...sessions.values()].map(s=>({...s,ageSeconds:Math.floor((Date.now()-s.started)/1000)}))},null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/catalog'){
      const f=safeWithin(CATALOG,u.searchParams.get('file')||'manifest.json');
      return send(res,200,await fs.readFile(f),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/search'){
      const q=(u.searchParams.get('q')||'').trim().toLowerCase();
      const type=(u.searchParams.get('type')||'').trim();
      if(!q && !type)return send(res,400,'q or type required');
      const rows=JSON.parse(await fs.readFile(path.join(CATALOG,'all.json'),'utf8'));
      const hit=rows.filter(r=>{
        if(type&&r.type!==type)return false;
        if(!q)return true;
        const hay=[r.path,r.file,r.short,r.name,r.command,...(r.ids||[])].filter(Boolean).join(' ').toLowerCase();
        return hay.includes(q);
      }).slice(0,500);
      return send(res,200,JSON.stringify({count:hit.length,results:hit},null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/world-audit'){return send(res,200,await fs.readFile(path.join(CATALOG,'world_audit.json')),'application/json; charset=utf-8');}
    if(u.pathname==='/api/triage'){return send(res,200,await fs.readFile(path.join(CATALOG,'triage.json')),'application/json; charset=utf-8');}
    if(u.pathname==='/api/source-status'){return send(res,200,await fs.readFile(path.join(CATALOG,'source_status.json')),'application/json; charset=utf-8');}
    if(u.pathname==='/api/dependency'){
      const graph=JSON.parse(await fs.readFile(path.join(CATALOG,'dependency_graph.json'),'utf8'));
      const pth=u.searchParams.get('path');
      return send(res,200,JSON.stringify(pth?(graph.entities[pth]||{incoming:[],outgoing:[]}):graph,null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/relations'){
      const pth=u.searchParams.get('path')||'';
      if(!pth)return send(res,400,'path required');
      const graph=JSON.parse(await fs.readFile(path.join(CATALOG,'reference_graph.json'),'utf8'));
      return send(res,200,JSON.stringify(graph.entities[pth]||{incoming:[],outgoing:[]},null,2),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/index'){
      const kind=(u.searchParams.get('kind')||'').trim();
      const allowed=new Set(['npc','item','skill','vendor','command','equipment','combat_npc','combat_core']);
      if(!allowed.has(kind))return send(res,400,'unsupported kind');
      const file=kind==='command'?'command_index.json':kind+'_index.json';
      return send(res,200,await fs.readFile(path.join(CATALOG,file)),'application/json; charset=utf-8');
    }
    if(u.pathname==='/api/entity'){
      const pth=u.searchParams.get('path')||'';
      if(!pth)return send(res,400,'path required');
      const rows=JSON.parse(await fs.readFile(path.join(CATALOG,'all.json'),'utf8'));
      const hit=rows.find(r=>r.path===pth);
      return hit?send(res,200,JSON.stringify(hit,null,2),'application/json; charset=utf-8'):send(res,404,'not found');
    }
    if(u.pathname==='/api/source'&&req.method==='GET'){
      // 原始碼與 mudlib/data（玩家存檔，含密碼雜湊和 email）只給主機本機的管理頁讀取。
      if(!isLocal(req))return send(res,403,'Source viewing is localhost-only');
      const rel=u.searchParams.get('path')||'';
      if(!rel.startsWith('mudlib/'))return send(res,400,'Only mudlib/* is editable');
      return send(res,200,await fs.readFile(safeWithin(UPSTREAM,rel),'utf8'),'text/plain; charset=utf-8');
    }
    if(u.pathname==='/api/source'&&req.method==='PUT'){
      if(!isLocal(req))return send(res,403,'Source editing is localhost-only');
      const rel=u.searchParams.get('path')||'';
      if(!rel.startsWith('mudlib/'))return send(res,400,'Only mudlib/* is editable');
      const f=safeWithin(UPSTREAM,rel),text=await bodyText(req);
      const before=await fs.readFile(f).catch(()=>Buffer.alloc(0));
      const beforeSha=before.length?crypto.createHash('sha256').update(before).digest('hex'):null;
      const afterBuf=Buffer.from(text,'utf8');
      const afterSha=crypto.createHash('sha256').update(afterBuf).digest('hex');
      const stamp=new Date().toISOString().replace(/[:.]/g,'-');
      const backup=path.join(ROOT,'patches',stamp+'__'+rel.replace(/[\\/]/g,'__')+'.bak');
      await fs.mkdir(path.dirname(backup),{recursive:true});
      if(before.length)await fs.writeFile(backup,before);
      await fs.writeFile(f,afterBuf);
      return send(res,200,JSON.stringify({saved:true,backup:before.length?path.relative(ROOT,backup):null,beforeSha256:beforeSha,afterSha256:afterSha},null,2),'application/json; charset=utf-8');
    }
    const rel=u.pathname==='/'?'index.html':u.pathname.replace(/^\/+/,''), file=safeWithin(WEB,rel);
    return send(res,200,await fs.readFile(file),mime[path.extname(file)]||'application/octet-stream');
  }catch(e){return send(res,e.code==='ENOENT'?404:500,e.message)}
});

const sessions=new Map();
let sessionSeq=0;
const bridgeLog=path.join(ROOT,'reports','bridge_runtime.log');
// 每個指令封包都記一行只在除錯時需要（BRIDGE_TRACE_PACKETS=1）：平常 30 人在線每秒要寫幾十行，
// 紀錄檔會長到數百 MB，而且同步寫檔會拖慢轉送。連線建立、關閉、錯誤照常記錄。
const TRACE_PACKETS=process.env.BRIDGE_TRACE_PACKETS==='1';
const BRIDGE_SECRET=loadBridgeSecret(MUDLIB);
function bridgeTrace(line){
  const text=`${new Date().toISOString()} ${line}\n`;
  try{fsSync.mkdirSync(path.dirname(bridgeLog),{recursive:true});fsSync.appendFileSync(bridgeLog,text)}catch{}
  console.log('[bridge]',line);
}
const wss=new WebSocketServer({server,path:'/mud',maxPayload:WS_MAX_PAYLOAD_BYTES});

// 斷線保留（docs/WEB_RESUME.md）：網頁連線斷掉時（例如手機切到別的 App），遊戲連線先不關，
// 替玩家保留 RESUME_HOLD_MS，期間的遊戲訊息存最多 RESUME_MAX_LINES 行；網頁帶著憑證回來就接回原本的連線。
// 憑證每次接回都換新的，只發給原本那個瀏覽器分頁。玩家用 #dis 主動斷線（關閉代碼 4000）就直接關掉。
const RESUME_HOLD_MS=Math.max(0,Number(process.env.RESUME_HOLD_MS??600000));
const RESUME_MAX_LINES=Math.max(0,Number(process.env.RESUME_MAX_LINES??500));
const RESUME_MAX_BYTES=262144;
const CLOSE_MANUAL=4000,CLOSE_REPLACED=4001;
const live=new Map();      // 工作階段編號 -> {row,tcp,ws,token,holdTimer,buffer}
const byToken=new Map();   // 憑證 -> 工作階段編號
const newToken=()=>crypto.randomBytes(18).toString('base64url');
function issueToken(s){
  if(s.token)byToken.delete(s.token);
  s.token=newToken();byToken.set(s.token,s.row.id);
  if(s.ws?.readyState===1)s.ws.send('@@BRIDGE|TOKEN|'+s.token);
}
// 保留期間的訊息只留最後 RESUME_MAX_LINES 行（也不超過 RESUME_MAX_BYTES）。
function keepTail(buf){
  if(buf.length>RESUME_MAX_BYTES)buf=buf.subarray(buf.length-RESUME_MAX_BYTES);
  let n=0;
  for(let i=buf.length-1;i>=0;i--){
    if(buf[i]===10&&++n>RESUME_MAX_LINES)return buf.subarray(i+1);
  }
  return buf;
}
function closeSession(s,why){
  if(s.closed||s.row.closing)return;s.closed=true;s.row.closing=true;
  clearTimeout(s.holdTimer);
  if(s.token)byToken.delete(s.token);
  live.delete(s.row.id);sessions.delete(s.row.id);
  if(!s.tcp.destroyed)s.tcp.destroy();
  if(s.ws&&s.ws.readyState<=1){try{s.ws.close(1011,'MUD TCP closed')}catch{}}
}
function holdSession(s){
  s.ws=null;s.row.parked=true;
  if(!s.row.tcpConnected||RESUME_HOLD_MS<=0||s.tcp.destroyed){closeSession(s,'closed');return;}
  bridgeTrace(`session ${s.row.id} held for resume (${Math.round(RESUME_HOLD_MS/1000)}s)`);
  clearTimeout(s.holdTimer);
  s.holdTimer=setTimeout(()=>{bridgeTrace(`session ${s.row.id} resume window expired`);closeSession(s,'expired');},RESUME_HOLD_MS);
}
// 把網頁連線接到工作階段上（新開或接回）。
function attach(s,ws){
  s.ws=ws;s.row.parked=false;clearTimeout(s.holdTimer);
  ws.isAlive=true;
  ws.on('pong',()=>{ws.isAlive=true});
  const row=s.row;
  ws.on('message',m=>{
    if(s.ws!==ws)return;
    const b=scrubRealIp(Buffer.from(m));row.bytesIn+=b.length;row.lastActivity=Date.now();
    // Length/timing only: useful for diagnosing pre-login automation without
    // ever recording usernames, passwords or command contents.
    if(TRACE_PACKETS)bridgeTrace(`session ${row.id} WS->MUD packet bytes=${b.length} total=${row.bytesIn}`);
    if(!s.tcp.destroyed)s.tcp.write(b);
  });
  // 通訊協定錯誤（例如訊息過大）不是意外斷線，不保留。單純的網路中斷不會走到這裡。
  let protocolError=false;
  ws.on('error',()=>{bridgeStats.wsErrors++;protocolError=true});
  ws.on('close',code=>{
    if(s.ws!==ws)return;               // 已被新的連線取代
    // 只有意外斷掉才保留：1006（連線突然中斷，例如手機切到背景、網路斷、心跳逾時）、1001（分頁離開）。
    // 其他關閉（正常關閉、玩家 #dis 的 4000、橋接程式自己因訊息過大或太慢而關掉）都直接結束。
    if(!protocolError&&(code===1006||code===1001))holdSession(s);
    else closeSession(s,'closed');
  });
}
wss.on('connection',(ws,req)=>{
  const u=new URL(req.url,'http://x');
  const resumeId=byToken.get(u.searchParams.get('resume')||'');
  const old=resumeId&&live.get(resumeId);
  if(old&&!old.closed&&!old.tcp.destroyed){
    // 接回：舊的網頁連線還沒被發現斷掉時先把它關掉（不關遊戲連線）。
    const prev=old.ws;old.ws=null;
    if(prev&&prev.readyState<=1){try{prev.close(CLOSE_REPLACED,'resumed elsewhere')}catch{}}
    attach(old,ws);
    const missed=old.buffer.length?old.buffer:null;old.buffer=Buffer.alloc(0);
    let lines=0;if(missed)for(const c of missed)if(c===10)lines++;
    old.row.resumes=(old.row.resumes||0)+1;
    bridgeTrace(`session ${old.row.id} resumed (${lines} lines replayed)`);
    ws.send(`@@BRIDGE|RESUMED|${lines}`);
    if(missed)ws.send(missed);
    issueToken(old);
    return;
  }
  if(sessions.size>=MAX_SESSIONS){
    bridgeStats.rejectedCapacity++;
    try{ws.send('\r\n[bridge] server at capacity, please retry later\r\n')}catch{}
    ws.close(1013,'server at capacity');return;
  }
  const id=++sessionSeq, started=Date.now();
  bridgeStats.accepted++;
  const tcp=net.createConnection({host:MUD_HOST,port:MUD_PORT});
  tcp.setNoDelay(true);
  // 第一行先告訴遊戲玩家的真實 IP（排在玩家任何輸入之前）。
  const realIp=realIpLine(req,BRIDGE_SECRET);
  if(realIp)tcp.write(realIp);
  const codec=new TelnetCodec(b=>{if(!tcp.destroyed)tcp.write(b)});
  const row={id,started,remote:req.socket.remoteAddress||'',bytesIn:0,bytesOut:0,lastActivity:started,tcpConnected:false,closing:false,parked:false};
  const s={row,tcp,ws:null,token:null,holdTimer:null,buffer:Buffer.alloc(0),closed:false};
  sessions.set(id,row);live.set(id,s);
  bridgeStats.peakSessions=Math.max(bridgeStats.peakSessions,sessions.size);
  // 結束這個工作階段（只做一次）：關遊戲連線、作廢憑證、從清單移除。
  const cleanup=()=>{sessions.delete(id);closeSession(s,'closed');};
  attach(s,ws);
  issueToken(s);
  const connectTimer=setTimeout(()=>{if(!row.tcpConnected&&!tcp.destroyed)tcp.destroy(new Error('MUD connect timeout'))},TCP_CONNECT_TIMEOUT_MS);
  tcp.on('connect',()=>{row.tcpConnected=true;row.lastActivity=Date.now();clearTimeout(connectTimer);bridgeTrace(`session ${id} TCP connected to ${MUD_HOST}:${MUD_PORT}`);if(s.ws?.readyState===1)s.ws.send('\r\n[ES2 connected]\r\n')});
  tcp.on('data',d=>{
    row.bytesOut+=d.length;row.lastActivity=Date.now();
    const clean=codec.feed(d);
    if(!clean.length)return;
    const ws=s.ws;
    if(!ws||ws.readyState!==1){
      // 網頁不在：先存起來，接回時補送。
      if(RESUME_MAX_LINES>0)s.buffer=keepTail(Buffer.concat([s.buffer,Buffer.from(clean)]));
      return;
    }
    if(ws.bufferedAmount>WS_MAX_BUFFERED_BYTES){
      try{ws.close(1013,'client too slow')}catch{}
      cleanup();
      return;
    }
    ws.send(clean);
  });
  tcp.on('error',e=>{bridgeStats.tcpErrors++;clearTimeout(connectTimer);bridgeTrace(`session ${id} TCP error: ${e.message}`);if(s.ws?.readyState===1)s.ws.send(`\r\n[bridge] ${e.message}\r\n`)});
  tcp.on('close',hadError=>{clearTimeout(connectTimer);bridgeTrace(`session ${id} TCP closed hadError=${hadError} bytesOut=${row.bytesOut} bytesIn=${row.bytesIn}`);cleanup()});
});
const ping=setInterval(()=>{
  for(const ws of wss.clients){
    if(ws.isAlive===false){ws.terminate();continue;}
    ws.isAlive=false;if(ws.readyState===1)ws.ping();
  }
},HEARTBEAT_MS);
server.on('close',()=>clearInterval(ping));
const shutdown=()=>{
  clearInterval(ping);
  for(const ws of wss.clients){try{ws.close(1001,'server shutdown')}catch{}}
  for(const x of live.values())closeSession(x,'server shutdown');
  for(const d of directServers){for(const c of d.sessions)c.destroy();d.close()}
  server.close(()=>process.exit(0));
  setTimeout(()=>process.exit(0),3000).unref();
};
process.once('SIGINT',shutdown);
process.once('SIGTERM',shutdown);
// zMUD（Big5）與 Telnet（UTF-8）直連入口；埠號設為 0 即關閉。見 docs/ZMUD_TELNET_PLAN.md
const DIRECT_HOST=process.env.DIRECT_HOST||'0.0.0.0';
const DIRECT_MAX=Math.max(1,Number(process.env.DIRECT_MAX_SESSIONS||MAX_SESSIONS));
const directOpts={host:DIRECT_HOST,mudHost:MUD_HOST,mudPort:MUD_PORT,maxSessions:DIRECT_MAX,connectTimeoutMs:TCP_CONNECT_TIMEOUT_MS,bridgeSecret:BRIDGE_SECRET,trace:bridgeTrace};
const directServers=[
  startDirectListener({...directOpts,name:'zmud',port:Number(process.env.ZMUD_PORT??4000),big5:true}),
  startDirectListener({...directOpts,name:'telnet',port:Number(process.env.TELNET_PORT??4003),big5:false}),
].filter(Boolean);
server.on('close',()=>{for(const d of directServers)d.close()});
server.listen(PORT,HOST,()=>console.log(`ES2 WebMUD http://${HOST}:${PORT} -> ${MUD_HOST}:${MUD_PORT}`));
