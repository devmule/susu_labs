const mongoose = require('mongoose')

const locationTypeEnum = [
	'Forest',
	'Desert',
	'Dungeon',
	'River',
	'Ocean'
]

const LocationSchema = new mongoose.Schema({
	locationId: {type: String, index: true, unique: true, required: true},
	description: {type: String, default: ''},
	locationType: {type: String, enum: locationTypeEnum, default: locationTypeEnum[0]},
});

module.exports = {
	Location: mongoose.model('Location', LocationSchema),
};
