const mongoose = require('mongoose');

const ItemTypeSchema = new mongoose.Schema({
	//id: {type: Number, index: true, unique: true},
	name: {type: String, required: true},
});

module.exports = mongoose.model('ItemType', ItemTypeSchema);
