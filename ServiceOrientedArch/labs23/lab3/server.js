require('./cities.js');
require('./game.js');
const ws = require('ws');

const wss = new ws.Server({port: 8003});
console.log('lab3 launched');

function broadcast(msg) {
	wss.clients.forEach(function each(client) {
		client.send(msg);
	});
}

/** @type CitiesGame */
let game = new global.CitiesGame(global.CITIES);
let lastSend = Date.now();

setInterval(() => {
	let time = Date.now();
	game.tick(time - lastSend);
	lastSend = time;
	if (game.isPlaying) broadcast(JSON.stringify({type: "time", time: game.time}));
}, 200);


game.addEventListener('message', (event) => {
	broadcast(JSON.stringify({type: "message", message: event.message}));
});

wss.on('connection', (user) => {
	
	let player = null;
	
	console.log('connected');
	user.onclose = () => {
		console.log('disconnected');
		game.playerExit(player);
	};
	user.onmessage = async (msg) => {
		try {
			let message = JSON.parse(msg.data);
			
			switch (message.type) {
				case "enter":
					player = new Player(message.name);
					game.playerEnter(player);
					break;
				
				case "city":
					game.tryGuessCity(message.city);
					break;
				
				case "start":
					game.play();
					break;
				
				
				default:
					user.close();
					game.playerExit(player);
			}
			
		} catch (e) {
			user.close();
			game.playerExit(player);
		}
	};
	
});
