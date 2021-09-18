const ws = require('ws');

const wss = new ws.Server({port: 8000});

wss.on('connection', (user) => {
	
	console.log('connected');
	user.onclose = () => console.log('disconnected');
	user.onmessage = (msg) => {
		try {
			
			let given_list = msg.data.split('\n').map(w => w.trim());
			let unique_list = given_list.filter((value, index, arr) => arr.indexOf(value) === index && value.length > 0);
			let sorted_list = unique_list.sort((a, b) => a.toLowerCase().localeCompare(b.toLowerCase()));
			
			user.send(sorted_list.join('\n'));
			
		} catch (e) {
			
			user.close();
			
		}
	};
	
});
