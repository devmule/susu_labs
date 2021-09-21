require('./cities.js');
const ws = require('ws');

const wss = new ws.Server({port: 8000});
