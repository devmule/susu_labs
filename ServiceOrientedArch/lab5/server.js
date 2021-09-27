const express = require('express');
const AdminBro = require('admin-bro');
AdminBro.registerAdapter(require('@admin-bro/mongoose'))
const expressAdminBro = require('@admin-bro/express');

const app = express();

app.get('/', (res) => res.send('Hello World'));

// Database
const connection = require('./database');
connection.once('open', () => console.log('Database connected Successfully'));
connection.on('error', (err) => console.log('Error', err));


const trackedModels = {
	...require('./models/Player'),
	...require('./models/Item'),
	...require('./models/Location'),
	...require('./models/Messages')
}
const adminBro = new AdminBro({resources: Object.values(trackedModels)});
app.use(adminBro.options.rootPath, expressAdminBro.buildRouter(adminBro))
app.listen(8000, () => console.log('Listening at Port 8000'));

// http:localhost:8000/admin
