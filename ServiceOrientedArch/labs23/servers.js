const https = require('http-server');

let server = https.createServer({});
server.listen(8080);

require('./lab2.1/server.js');
require('./lab2.2/server.js');
require('./lab3/server.js');

