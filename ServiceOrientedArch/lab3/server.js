const CITIES = require('./cities.js');
require('./game.js');
const ws = require('ws');

const wss = new ws.Server({port: 8000});

/** @type CitiesGame */
let game = new global.CitiesGame(CITIES);

wss.on('connection', (user) => {
	
	let player = null;
	
	console.log('connected');
	user.onclose = () => {
		console.log('disconnected');
		game?.playerExit(player);
	};
	user.onmessage = async (msg) => {
		try {
			let message = JSON.parse(msg.data);
			
			switch (message.type) {
				case "enter":
					player = new Player(message.name);
					game?.playerEnter(player);
					break;
				
				case "city":
					game?.tryGuessCity(message.city);
					break;
					
					
				default:
					user.close();
					game?.playerExit(player);
			}
			
		} catch (e) {
			user.close();
			game?.playerExit(player);
		}
	};
	
});
