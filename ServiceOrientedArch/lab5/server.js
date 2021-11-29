const express = require('express');

const app = express();

const connection = require('./database');
connection.once('open', () => console.log('Database connected Successfully'));
connection.on('error', (err) => console.log('Error', err));


//
//
// admin panel http:localhost:8000/admin
// Requirements
const mongoose = require('mongoose')
const AdminBro = require('admin-bro')
const AdminBroExpressjs = require('@admin-bro/express')

// We have to tell AdminBro that we will manage mongoose resources with it
AdminBro.registerAdapter(require('@admin-bro/mongoose'))

// Resources definitions
const User = require("./models/User");

// Pass all configuration settings to AdminBro
const adminBro = new AdminBro({
	resources: [
		{
			resource: User,
			options: {
				properties: {
					encryptedPassword: {
						isVisible: false,
					},
					password: {
						type: 'string',
						isVisible: {
							list: false, edit: true, filter: false, show: false,
						},
					},
				},
				actions: {
					new: {
						before: async (request) => {
							if (request.payload.password) {
								request.payload = {
									...request.payload,
									encryptedPassword: request.payload.password,
									password: undefined,
								}
							}
							return request
						},
					}
				}
			},
		},
		require('./models/Player.js'),
		require('./models/Item.js'),
		require('./models/ItemType.js'),
		require('./models/Location.js'),
		require('./models/Messages.js')
	],
	rootPath: '/admin',
})

// Build and use a router which will handle all AdminBro routes
// Build and use a router which will handle all AdminBro routes
const router = AdminBroExpressjs.buildAuthenticatedRouter(adminBro, {
	authenticate: async (email, password) => {
		const user = await User.findOne({email})
		if (user) {
			const matched = password === user.encryptedPassword;
			if (matched) return user;
		}
		return false;
	},
	cookiePassword: 'some-secret-password-used-to-secure-cookie',
})

app.use(adminBro.options.rootPath, router)

// Running the server
const run = async () => {
	await mongoose.connect('mongodb://localhost:27017/lab5db', {useNewUrlParser: true})
	await app.listen(8080, () => console.log(`App listening on port 8080!`))
}

run().then(r => null);
