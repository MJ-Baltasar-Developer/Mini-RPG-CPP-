// Usage: node server.js [path-to-game-exe]   (default: ./rpg or rpg.exe)
const http = require('http'), fs = require('fs'), path = require('path');
const { spawn } = require('child_process');

const exe = path.resolve(process.argv[2] || (process.platform === 'win32' ? 'rpg.exe' : 'rpg'));
const PORT = process.env.PORT || 3000;
let proc = null, history = [];
const clients = new Set();

function emit(ev) {
  history.push(ev);
  const s = `data: ${JSON.stringify(ev)}\n\n`;
  clients.forEach(r => r.write(s));
}

function start() {
  const old = proc; proc = null;
  if (old) old.kill();
  history = [];
  clients.forEach(r => r.write('data: {"t":"reset"}\n\n'));
  const p = spawn(exe, [], { stdio: ['pipe', 'pipe', 'pipe'] });
  proc = p;
  p.stdout.on('data', d => emit({ t: 'out', d: d.toString() }));
  p.stderr.on('data', d => emit({ t: 'err', d: d.toString() }));
  p.stdin.on('error', () => {});
  p.on('error', e => emit({ t: 'err', d: `Could not start ${exe}: ${e.message}` }));
  p.on('exit', () => { if (proc === p) { proc = null; emit({ t: 'exit' }); } });
}

http.createServer((req, res) => {
  if (req.method === 'GET' && req.url === '/') {
    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    return res.end(fs.readFileSync(path.join(__dirname, 'index.html')));
  }
  if (req.method === 'GET' && req.url === '/events') {
    res.writeHead(200, { 'Content-Type': 'text/event-stream', 'Cache-Control': 'no-cache', Connection: 'keep-alive' });
    clients.add(res);
    history.forEach(ev => res.write(`data: ${JSON.stringify(ev)}\n\n`));
    return req.on('close', () => clients.delete(res));
  }
  if (req.method === 'POST' && (req.url === '/input' || req.url === '/restart')) {
    let body = '';
    req.on('data', c => (body += c));
    req.on('end', () => {
      if (req.url === '/restart') start();
      else if (proc) proc.stdin.write(body.replace(/[\r\n]+/g, ' ').trim() + '\n');
      res.writeHead(204); res.end();
    });
    return;
  }
  res.writeHead(404); res.end();
}).listen(PORT, () => {
  console.log(`RPG frontend: http://localhost:${PORT}\nGame binary:  ${exe}`);
  start();
});
