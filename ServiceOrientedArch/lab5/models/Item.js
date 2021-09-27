const mongoose = require('mongoose');

const ItemTypeSchema = new mongoose.Schema({
	//id: {type: Number, index: true, unique: true},
	name: {type: String, required: true},
});

const ItemSchema = new mongoose.Schema({
	itemType: {type: mongoose.Types.ObjectId, ref: 'ItemType'},
	quality: {type: Number, min: 0, max: 100, default: 100},
	owner: {type: mongoose.Types.ObjectId, ref: 'Player'},
});

module.exports = {
	ItemType: mongoose.model('ItemType', ItemTypeSchema),
	Item: mongoose.model('Item', ItemSchema),
};
