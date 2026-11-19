// 聊天視窗：可拖曳、可調整大小的浮動視窗，依時間順序列出各頻道訊息。
// 「全部」顯示所有頻道；個別頻道可複選，選到的頻道依時間交錯顯示。
// 訊息只留在記憶體（最近 500 筆，重新整理即清空）；視窗位置、大小與選取的頻道記在瀏覽器。

import {makeResizable} from './float_window.js';

const STORAGE_KEY='es2-chat-window-v1';
const MAX_MESSAGES=500;
export const CHAT_CHANNELS=['chat','rumor','tell','say'];

const esc=s=>String(s??'').replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
const pad=n=>String(n).padStart(2,'0');
// 2026/10/12/00:37:40
export function formatChatTime(d){
  return `${d.getFullYear()}/${pad(d.getMonth()+1)}/${pad(d.getDate())}/${pad(d.getHours())}:${pad(d.getMinutes())}:${pad(d.getSeconds())}`;
}

export function setupChatWindow({root,openButton}){
  if(!root)return {add(){}};
  const log=root.querySelector('[data-chat-log]');
  const head=root.querySelector('[data-chat-drag]');
  const messages=[];
  let selected=new Set();   // 空集合 = 全部
  let geometry=null;

  try{
    const saved=JSON.parse(localStorage.getItem(STORAGE_KEY)||'null');
    if(saved&&typeof saved==='object'){
      if(Array.isArray(saved.selected))selected=new Set(saved.selected.filter(x=>CHAT_CHANNELS.includes(x)));
      if(saved.geometry&&typeof saved.geometry==='object')geometry=saved.geometry;
    }
  }catch(_){}
  function persist(){
    try{localStorage.setItem(STORAGE_KEY,JSON.stringify({selected:[...selected],geometry}));}catch(_){}
  }

  const visible=m=>!selected.size||selected.has(m.channel);
  function rowHtml(m){
    return `<div class="chat-line chat-${m.channel}" title="${esc(formatChatTime(m.time))}">${esc(m.text)}</div>`;
  }
  function renderAll(){
    const rows=messages.filter(visible);
    log.innerHTML=rows.length?rows.map(rowHtml).join(''):'<div class="chat-empty">目前沒有訊息。</div>';
    log.scrollTop=log.scrollHeight;
  }
  function renderButtons(){
    for(const b of root.querySelectorAll('[data-chat-channel]')){
      const id=b.dataset.chatChannel;
      const on=id==='all'?!selected.size:selected.has(id);
      b.classList.toggle('active',on);b.setAttribute('aria-pressed',on?'true':'false');
    }
  }

  // 新訊息只接在最後面，不會自動捲到最新；捲軸停在玩家目前看的位置（使用者指示，2026-11-19）。
  function add(channel,text,time=new Date()){
    const m={channel,text:String(text),time};
    messages.push(m);
    let dropped=[];
    if(messages.length>MAX_MESSAGES)dropped=messages.splice(0,messages.length-MAX_MESSAGES);
    if(root.hidden)return;
    // 超過 500 筆時拿掉最舊的幾行；畫面上的內容往上移了多少，捲軸就跟著補回多少，看的位置不變。
    for(const old of dropped){
      if(!visible(old))continue;
      const first=log.querySelector('.chat-line');if(!first)break;
      const h=first.offsetHeight;first.remove();log.scrollTop=Math.max(0,log.scrollTop-h);
    }
    if(!visible(m))return;
    log.querySelector('.chat-empty')?.remove();
    const top=log.scrollTop;
    log.insertAdjacentHTML('beforeend',rowHtml(m));
    log.scrollTop=top;
  }

  // ---------- 頻道選擇 ----------
  root.addEventListener('click',e=>{
    const b=e.target instanceof Element?e.target.closest('button'):null;
    if(!b)return;
    if(b.dataset.chatChannel){
      const id=b.dataset.chatChannel;
      if(id==='all')selected.clear();
      else if(selected.has(id))selected.delete(id);
      else selected.add(id);
      // 個別頻道全部選滿等同「全部」，全部取消也回到「全部」。
      if(selected.size===CHAT_CHANNELS.length)selected.clear();
      persist();renderButtons();renderAll();
    }else if(b.hasAttribute('data-chat-close')){
      close();
    }else if(b.hasAttribute('data-chat-download')){
      download();
    }
  });

  // ---------- 下載 ----------
  function download(){
    const rows=messages.filter(visible);
    const text=rows.map(m=>`${formatChatTime(m.time)} ${m.text}`).join('\r\n')+(rows.length?'\r\n':'');
    const now=new Date();
    const stamp=`${now.getFullYear()}${pad(now.getMonth()+1)}${pad(now.getDate())}-${pad(now.getHours())}${pad(now.getMinutes())}${pad(now.getSeconds())}`;
    const a=document.createElement('a');
    // 加 BOM，Windows 記事本開啟才不會變亂碼。
    a.href=URL.createObjectURL(new Blob(['﻿'+text],{type:'text/plain;charset=utf-8'}));
    a.download=`es2-chat-${stamp}.txt`;
    document.body.appendChild(a);a.click();
    setTimeout(()=>{a.remove();URL.revokeObjectURL(a.href);},1000);
  }

  // ---------- 位置與大小 ----------
  function clampIntoView(){
    const r=root.getBoundingClientRect();
    const maxLeft=Math.max(0,window.innerWidth-Math.min(r.width,window.innerWidth));
    const maxTop=Math.max(0,window.innerHeight-48);
    const left=Math.min(Math.max(0,r.left),maxLeft);
    const top=Math.min(Math.max(0,r.top),maxTop);
    root.style.left=left+'px';root.style.top=top+'px';
  }
  function applyGeometry(){
    if(geometry){
      root.style.left=geometry.left+'px';root.style.top=geometry.top+'px';
      if(geometry.width)root.style.width=geometry.width+'px';
      if(geometry.height)root.style.height=geometry.height+'px';
    }else{
      // 第一次打開：放在畫面中間偏上。
      const w=Math.min(720,window.innerWidth-32),h=Math.min(420,window.innerHeight-80);
      root.style.width=w+'px';root.style.height=h+'px';
      root.style.left=Math.max(16,(window.innerWidth-w)/2)+'px';
      root.style.top=Math.max(16,(window.innerHeight-h)/3)+'px';
    }
    clampIntoView();
  }
  function saveGeometry(){
    const r=root.getBoundingClientRect();
    geometry={left:Math.round(r.left),top:Math.round(r.top),width:Math.round(r.width),height:Math.round(r.height)};
    persist();
  }

  let drag=null;
  head.addEventListener('pointerdown',e=>{
    if(e.button!==0||(e.target instanceof Element&&e.target.closest('button')))return;
    const r=root.getBoundingClientRect();
    drag={dx:e.clientX-r.left,dy:e.clientY-r.top,id:e.pointerId};
    head.setPointerCapture(e.pointerId);
    root.classList.add('is-dragging');
    e.preventDefault();
  });
  head.addEventListener('pointermove',e=>{
    if(!drag||e.pointerId!==drag.id)return;
    root.style.left=(e.clientX-drag.dx)+'px';
    root.style.top=(e.clientY-drag.dy)+'px';
    clampIntoView();
  });
  const endDrag=e=>{
    if(!drag||e.pointerId!==drag.id)return;
    drag=null;root.classList.remove('is-dragging');
    saveGeometry();
  };
  head.addEventListener('pointerup',endDrag);
  head.addEventListener('pointercancel',endDrag);

  // 拖拉上下左右邊線與四個角落調整大小，放開後記住。
  makeResizable(root,{onEnd:saveGeometry});
  window.addEventListener('resize',()=>{if(!root.hidden)clampIntoView();});

  // ---------- 開關 ----------
  function open(){
    root.hidden=false;
    applyGeometry();renderButtons();renderAll();
    openButton?.classList.add('active');openButton?.setAttribute('aria-pressed','true');
  }
  function close(){
    root.hidden=true;
    openButton?.classList.remove('active');openButton?.setAttribute('aria-pressed','false');
  }
  openButton?.addEventListener('click',()=>{if(root.hidden)open();else close();});

  renderButtons();
  return {add,open,close};
}
