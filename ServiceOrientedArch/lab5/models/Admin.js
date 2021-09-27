const mongoose = require('mongoose')

const AdminSchema = new mongoose.Schema({
	name: String,
	email: String,
	password: String
});

module.exports = {
	Admin: mongoose.model('Admin', AdminSchema),
};
