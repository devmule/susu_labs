const mongoose = require('mongoose')

const MessagesSchema = new mongoose.Schema({
	//messageId: {type: Number, index: true, unique: true},
	playerFrom: {type: mongoose.Types.ObjectId, ref: 'Player'},
	playerTo: {type: mongoose.Types.ObjectId, ref: 'Player'},
	messageText: {
		type: String, validate: {
			validator: text => text.length <= 1000,
			message: 'Max text length is 1000 symbols'
		}
	},
});

module.exports = mongoose.model('Messages', MessagesSchema);
