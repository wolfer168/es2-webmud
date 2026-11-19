#!/usr/bin/env node
import net from 'node:net';
import fs from 'node:fs';
import path from 'node:path';
import {spawn} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import WebSocket from '../server/node_modules/ws/index.js';

const here=path.dirname(fileURLToPath(import.meta.url));
const root=path.resolve(here,'..');
const version=fs.readFileSync(path.join(root,'VERSION'),'utf8').trim();
const wait=ms=>new Promise(r=>setTimeout(r,ms));
async function freePort(){const s=net.createServer();await new Promise((r,j)=>{s.once('error',j);s.listen(0,'127.0.0.1',r)});const p=s.address().port;await new Promise(r=>s.close(r));return p;}
async function waitUntil(fn,ms=5000,step=50){const end=Date.now()+ms;while(Date.now()<end){if(await fn())return true;await wait(step)}return false;}
async function health(port){try{return await fetch(`http://127.0.0.1:${port}/api/multiplayer-health`).then(r=>r.json())}catch{return null}}

async function startBridge({mudPort,env={}}){
  const webPort=await freePort();
  const child=spawn(process.execPath,['server/index.js'],{cwd:root,env:{...process.env,HOST:'127.0.0.1',PORT:String(webPort),MUD_HOST:'127.0.0.1',MUD_PORT:String(mudPort),HEARTBEAT_MS:'5000',TCP_CONNECT_TIMEOUT_MS:'1200',...env},stdio:['ignore','pipe','pipe']});
  let log='';child.stdout.on('data',d=>log+=String(d));child.stderr.on('data',d=>log+=String(d));
  const ok=await waitUntil(()=>log.includes('ES2 WebMUD'),5000);
  if(!ok){try{child.kill('SIGKILL')}catch{};throw new Error('bridge did not start: '+log)}
  return {child,webPort,getLog:()=>log};
}
async function stopBridge(b){if(!b?.child)return;try{b.child.kill('SIGTERM')}catch{};await wait(150);if(b.child.exitCode===null)try{b.child.kill('SIGKILL')}catch{}}
async function closeServer(s){if(!s)return;await new Promise(r=>{try{s.close(()=>r())}catch{r()}})}

async function scenarioBackendUnavailable(){
  const mudPort=await freePort(); // deliberately leave it closed
  const b=await startBridge({mudPort});let text='',closed=false;
  const ws=new WebSocket(`ws://127.0.0.1:${b.webPort}/mud`);
  ws.on('message',d=>text+=String(d));ws.on('close',()=>closed=true);ws.on('error',()=>{});
  await waitUntil(()=>closed,4000);await wait(100);
  const h=await health(b.webPort);const ok=closed && h?.sessions?.active===0 && h?.totals?.tcpErrors>=1 && /bridge/i.test(text);
  await stopBridge(b);return {name:'backend-unavailable-cleanup',ok,closed,bridgeMessageSeen:/bridge/i.test(text),health:h};
}

async function scenarioBackendDisconnect(){
  const mudPort=await freePort();const sockets=new Set();
  const mud=net.createServer(sock=>{sockets.add(sock);let ending=false;sock.on('error',()=>{});sock.write('READY\r\n');sock.on('data',()=>{if(ending||sock.destroyed||sock.writableEnded)return;ending=true;sock.write('BACKEND-BYE\r\n');setTimeout(()=>{if(!sock.destroyed)sock.end()},20)});sock.on('close',()=>sockets.delete(sock))});
  await new Promise((r,j)=>{mud.once('error',j);mud.listen(mudPort,'127.0.0.1',r)});
  const b=await startBridge({mudPort});let text='',closed=false;
  const ws=new WebSocket(`ws://127.0.0.1:${b.webPort}/mud`);ws.on('message',d=>{text+=String(d);if(text.includes('READY'))ws.send('probe\r\n')});ws.on('close',()=>closed=true);ws.on('error',()=>{});
  await waitUntil(()=>closed,4000);await wait(100);const h=await health(b.webPort);
  const ok=closed && text.includes('BACKEND-BYE') && h?.sessions?.active===0;
  try{ws.terminate()}catch{};for(const s of sockets)s.destroy();await stopBridge(b);await closeServer(mud);return {name:'backend-disconnect-propagates',ok,closed,backendByeSeen:text.includes('BACKEND-BYE'),health:h};
}

async function scenarioClientAbruptDisconnect(){
  const mudPort=await freePort();let accepted=0,closed=0;const sockets=new Set();
  const mud=net.createServer(sock=>{accepted++;sockets.add(sock);sock.on('error',()=>{});sock.write('READY\r\n');sock.on('close',()=>{closed++;sockets.delete(sock)})});
  await new Promise((r,j)=>{mud.once('error',j);mud.listen(mudPort,'127.0.0.1',r)});
  // 網頁連線突然中斷時，橋接程式會先保留遊戲連線一段時間讓玩家接回（docs/WEB_RESUME.md）；
  // 這裡把保留時間設短，確認時間到了遊戲連線一樣會被清掉，不會殘留。
  const b=await startBridge({mudPort,env:{RESUME_HOLD_MS:'500'}});let ready=false;
  const ws=new WebSocket(`ws://127.0.0.1:${b.webPort}/mud`);ws.on('message',d=>{if(String(d).includes('READY'))ready=true});ws.on('error',()=>{});
  await waitUntil(()=>ready,3000);ws.terminate();
  const cleaned=await waitUntil(async()=>{const h=await health(b.webPort);return h?.sessions?.active===0 && closed>=1},3000);
  const h=await health(b.webPort);const ok=ready && accepted===1 && closed>=1 && cleaned;
  for(const s of sockets)s.destroy();await stopBridge(b);await closeServer(mud);return {name:'abrupt-client-disconnect-cleanup',ok,acceptedBackendSockets:accepted,closedBackendSockets:closed,health:h};
}

async function scenarioBackendFailureIsolation(){
  const mudPort=await freePort();let seq=0;const sockets=new Map();
  const mud=net.createServer(sock=>{const id=++seq;sockets.set(id,sock);sock.on('error',()=>{});sock.write(`READY:${id}\r\n`);sock.on('data',d=>{const s=String(d);if(s.includes('DROP'))sock.destroy();else sock.write(`ECHO:${id}:${s}`)});sock.on('close',()=>sockets.delete(id))});
  await new Promise((r,j)=>{mud.once('error',j);mud.listen(mudPort,'127.0.0.1',r)});
  const b=await startBridge({mudPort});
  const make=label=>new Promise((resolve,reject)=>{const ws=new WebSocket(`ws://127.0.0.1:${b.webPort}/mud`);let text='';const t=setTimeout(()=>reject(new Error(label+' ready timeout '+text)),3000);ws.on('message',d=>{text+=String(d);const m=text.match(/READY:(\d+)/);if(m){clearTimeout(t);resolve({ws,id:Number(m[1]),textRef:()=>text})}});ws.on('error',reject)});
  const a=await make('A'),c=await make('B');
  a.ws.send('DROP\r\n');await wait(150);c.ws.send('KEEP\r\n');
  const survived=await waitUntil(()=>c.textRef().includes(`ECHO:${c.id}:KEEP`),3000);const h=await health(b.webPort);
  const ok=a.id!==c.id && survived && h?.sessions?.active===1;
  try{a.ws.terminate()}catch{};try{c.ws.close()}catch{};for(const s of sockets.values())s.destroy();await wait(100);await stopBridge(b);await closeServer(mud);return {name:'one-backend-failure-does-not-cross-kill',ok,tcpA:a.id,tcpB:c.id,secondSessionSurvived:survived,activeAfterFirstDrop:h?.sessions?.active};
}

async function scenarioOversizePayload(){
  const mudPort=await freePort();let seq=0;const sockets=new Set();
  const mud=net.createServer(sock=>{const id=++seq;sockets.add(sock);sock.on('error',()=>{});sock.write(`READY:${id}\r\n`);sock.on('data',d=>sock.write(`ECHO:${id}:${String(d)}`));sock.on('close',()=>sockets.delete(sock))});
  await new Promise((r,j)=>{mud.once('error',j);mud.listen(mudPort,'127.0.0.1',r)});
  const b=await startBridge({mudPort,env:{WS_MAX_PAYLOAD_BYTES:'4096'}});let closeCode=null;
  const bad=new WebSocket(`ws://127.0.0.1:${b.webPort}/mud`);bad.on('open',()=>bad.send('X'.repeat(8192)));bad.on('close',c=>closeCode=c);bad.on('error',()=>{});
  await waitUntil(()=>closeCode!==null,3000);await wait(100);
  let text='',goodReady=false,goodEcho=false;const good=new WebSocket(`ws://127.0.0.1:${b.webPort}/mud`);good.on('message',d=>{text+=String(d);if(/READY:\d+/.test(text)&&!goodReady){goodReady=true;good.send('SAFE\r\n')}if(/ECHO:\d+:SAFE/.test(text))goodEcho=true});good.on('error',()=>{});
  await waitUntil(()=>goodEcho,3000);const h=await health(b.webPort);
  const ok=closeCode===1009 && goodEcho && h?.sessions?.active===1;
  try{bad.terminate()}catch{};try{good.close()}catch{};for(const s of sockets)s.destroy();await wait(100);await stopBridge(b);await closeServer(mud);return {name:'oversize-websocket-is-contained',ok,oversizeCloseCode:closeCode,healthySessionAfterward:goodEcho,health:h};
}

const scenarios=[];let fatal=null;
for(const fn of [scenarioBackendUnavailable,scenarioBackendDisconnect,scenarioClientAbruptDisconnect,scenarioBackendFailureIsolation,scenarioOversizePayload]){
  try{const r=await fn();scenarios.push(r);console.log(`${r.ok?'[PASS]':'[FAIL]'} ${r.name}`)}catch(e){const r={name:fn.name,ok:false,error:String(e?.stack||e)};scenarios.push(r);console.error('[FAIL]',fn.name,e);fatal=e}
}
const ok=!fatal&&scenarios.every(x=>x.ok);
const out={schema:1,version,generated:new Date().toISOString(),scope:'OFFLINE fake-MUD fault injection only; no live gameplay claim',ok,scenarios,liveAcceptanceClaimed:false};
const outPath=path.join(root,'reports','multiplayer_fault_matrix_report.json');fs.mkdirSync(path.dirname(outPath),{recursive:true});fs.writeFileSync(outPath,JSON.stringify(out,null,2));
console.log(JSON.stringify(out,null,2));
process.exit(ok?0:2);
