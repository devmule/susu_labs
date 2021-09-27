const mongoose = require('mongoose');

const ItemSchema = new mongoose.Schema({
	itemType: {type: mongoose.Types.ObjectId, ref: 'ItemType'},
	quality: {type: Number, min: 0, max: 100, default: 100},
	owner: {type: mongoose.Types.ObjectId, ref: 'Player'},
});

module.exports = mongoose.model('Item', ItemSchema);
