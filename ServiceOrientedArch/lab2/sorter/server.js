const ws = require('ws');

const wss = new ws.Server({port: 8000});

wss.on('connection', (user) => {
	
	console.log('connected');
	user.onclose = () => console.log('disconnected');
	user.onmessage = (msg) => {
		try {
			
			let given_list = JSON.parse(msg.data);
			let unique_list = given_list.filter((value, index, arr) => arr.indexOf(value) === index);
			let sorted_list = unique_list.sort((a, b) => a.toLowerCase().localeCompare(b.toLowerCase()));
			
			user.send(JSON.stringify(sorted_list));
			
		} catch (e) {
			
			user.close();
			
		}
	};
	
});
