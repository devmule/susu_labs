const mongoose = require('mongoose')

const playerclassEnum = [
	'Knight',
	'Wizard',
	'Thief',
	'Paladin',
]


const PlayerSchema = new mongoose.Schema({
	//id: {type: Number, index: true, unique: true},
	name: {type: String, default: 'player'},
	playerclass: {type: String, enum: playerclassEnum, default: playerclassEnum[0]},
	email: {type: String, default: ''},
	level: {type: Number, default: 0},
	position: {type: mongoose.Types.ObjectId, ref: 'Location'},
});

module.exports = {
	Player: mongoose.model('Player', PlayerSchema),
};
