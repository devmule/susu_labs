const express = require('express');

let collectionCRUD = (Collection) => {
	
	const create = (req, res) => {
		const newEntry = req.body;
		Collection.create(newEntry, (e, newEntry) => {
			if (e) res.sendStatus(500);
			else res.send(newEntry);
		});
	};
	const readMany = (req, res) => {
		let query = res.locals.query || {};
		Collection.find(query, (e, result) => {
			if (e) res.status(500).send(e);
			else res.send(result);
		});
	};
	const readOne = (req, res) => {
		Collection.findById(req.params._id, (e, result) => {
			if (e) res.status(500).send(e);
			else res.send(result);
		});
	};
	const update = (req, res) => {
		const changedEntry = req.body;
		Collection.update({_id: req.params._id}, {$set: changedEntry}, (e) => {
			if (e) res.sendStatus(500);
			else res.sendStatus(200);
		});
	};
	const remove = (req, res) => {
		Collection.remove({_id: req.params._id}, (e) => {
			if (e) res.status(500).send(e);
			else res.sendStatus(200);
		});
	};
	
	
	let router = express.Router();
	
	router.post('/', create);
	router.get('/', readMany);
	router.get('/:_id', readOne);
	router.put('/:_id', update);
	router.delete('/:_id', remove);
	
	return router;
	
};


const api = express.Router();

api.use('/Item', collectionCRUD(require('./models/Item.js')));
api.use('/ItemType', collectionCRUD(require('./models/ItemType.js')));
api.use('/Location', collectionCRUD(require('./models/Location.js')));
api.use('/Messages', collectionCRUD(require('./models/Messages.js')));
api.use('/Player', collectionCRUD(require('./models/Player.js')));


module.exports = api;
