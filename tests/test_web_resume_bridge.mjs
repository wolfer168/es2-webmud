#!/usr/bin/env node
// 網頁斷線保留（docs/WEB_RESUME.md）：只有手機網頁（hold=1）保留，電腦版斷線就結束。
import net from 'node:net';
import path from 'node:path';
import {spawn} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import assert from 'node:assert/strict';
import WebSocket from '../server/node_modules/ws/index.js';

const root=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..');
const wait=ms=>new Promise(r=>setTimeout(r,ms));
async function freePort(){const s=net.createServer();await new Promise(r=>s.listen(0,'127.0.0.1',r));const p=s.address().port;await new Promise(r=>s.close(r));return p;}
async function until(fn,ms=4000){const end=Date.now()+ms;while(Date.now()<end){if(await fn())return true;await wait(30);}return false;}

// 假的遊戲：每條連線記下來，收到什麼就回 ECHO。
const mudConns=[];
const mud=net.createServer(c=>{mudConns.push(c);c.on('error',()=>{});c.write('LOGIN?\r\n');c.on('data',d=>c.write('ECHO:'+String(d)));});
await new Promise(r=>mud.listen(0,'127.0.0.1',r));
const webPort=await freePort();
const child=spawn(process.execPath,['server/index.js'],{cwd:root,stdio:['ignore','pipe','pipe'],
  env:{...process.env,HOST:'127.0.0.1',PORT:String(webPort),MUD_HOST:'127.0.0.1',MUD_PORT:String(mud.address().port),RESUME_HOLD_MS:'5000'}});
let log='';child.stdout.on('data',d=>log+=d);child.stderr.on('data',d=>log+=d);
try{
  assert.ok(await until(()=>log.includes('ES2 WebMUD')),'bridge start: '+log);
  function open(q){
    const ws=new WebSocket(`ws://127.0.0.1:${webPort}/mud${q}`);const st={ws,text:'',token:''};
    ws.on('message',d=>{const s=String(d);const m=s.match(/@@BRIDGE\|TOKEN\|(\S+)/);if(m)st.token=m[1];st.text+=s;});
    ws.on('error',()=>{});return st;
  }
  // 電腦版：不發憑證；網頁連線突然斷掉，遊戲連線也馬上關掉。
  const pc=open('');
  assert.ok(await until(()=>pc.text.includes('LOGIN?')));
  await wait(100);assert.equal(pc.token,'');
  const pcMud=mudConns.at(-1);let pcClosed=false;pcMud.on('close',()=>pcClosed=true);
  pc.ws.terminate();
  assert.ok(await until(()=>pcClosed,2000),'PC session should close at once');

  // 手機：有憑證；突然斷掉後保留，帶憑證接回同一條遊戲連線並補上錯過的訊息。
  const ph=open('?hold=1');
  assert.ok(await until(()=>ph.token&&ph.text.includes('LOGIN?')));
  const phMud=mudConns.at(-1);let phClosed=false;phMud.on('close',()=>phClosed=true);
  ph.ws.terminate();await wait(200);
  assert.equal(phClosed,false,'phone session should be held');
  phMud.write('MISSED\r\n');await wait(100);
  const back=open(`?hold=1&resume=${encodeURIComponent(ph.token)}`);
  assert.ok(await until(()=>back.text.includes('@@BRIDGE|RESUMED|')&&back.text.includes('MISSED')));
  back.ws.send('hi\r\n');
  assert.ok(await until(()=>back.text.includes('ECHO:hi')));
  assert.equal(mudConns.length,2,'resume must reuse the held MUD connection');
  back.ws.close(4000,'manual');
  assert.ok(await until(()=>phClosed,2000));
  console.log('web resume bridge tests passed');
}finally{child.kill('SIGTERM');mud.close();for(const c of mudConns)c.destroy();}
