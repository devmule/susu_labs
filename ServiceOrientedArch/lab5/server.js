const express = require('express');

const app = express();

app.get('/', (res) => res.send('Hello World'));
app.use('/api', require('./api.js'));

const connection = require('./database');
connection.once('open', () => console.log('Database connected Successfully'));
connection.on('error', (err) => console.log('Error', err));


//
//
// admin panel http:localhost:8000/admin
const AdminBro = require('admin-bro');
AdminBro.registerAdapter(require('@admin-bro/mongoose'))
const expressAdminBro = require('@admin-bro/express');
const adminBro = new AdminBro({
	resources: [
		require('./models/Player.js'),
		require('./models/Item.js'),
		require('./models/ItemType.js'),
		require('./models/Location.js'),
		require('./models/Messages.js')
	]
});
app.use('/admin', expressAdminBro.buildRouter(adminBro))


//
//
// http:localhost:8000/api/Item
app.listen(8000, () => console.log('Listening at Port 8000'));
