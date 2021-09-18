function main(url) {
	
	const socket = new WebSocket(url);
	
	const send_btn = document.getElementById('send');
	const input_area = document.getElementById('input');
	const output_area = document.getElementById('output');
	
	send_btn.onclick = () => socket.send(JSON.stringify(input_area.value.replace('\n', '').split(',').map(w => w.trim())))
	
	socket.addEventListener('open', () => alert('соединение установлено'));
	socket.addEventListener('close', () => alert('соединение потеряно'));
	socket.addEventListener('error', () => alert('соединение потеряно'));
	socket.addEventListener('message', e => output_area.value = JSON.parse(e.data).join(', '));
	
	
}
