import {CitiesGame, Player} from "./game.js";

class GameScreen {
	constructor() {
		/**
		 * @abstract
		 * @type {HTMLElement}
		 * */
		this.screen = null;
	}
}


export class HotSeat extends GameScreen {
	constructor() {
		super();
		this.screen = document.createElement('div');
		this.screen.innerHTML = `

<label for="name_input">введите имя</label>
<br>
<textarea name="name_input" id="name_input" cols="30" rows="1"></textarea>
<br>
<button id="name_btn">добавить</button>
<br>
<br>
<button id="start_game">начать игру</button>


<br>
<br>
<br>

<label for="city_input">введите город</label><br>
<textarea name="city_input" id="city_input" cols="30" rows="1"></textarea><br>
<button id="city_send">отправить город</button>
<br>
<br>
<label for="messages_log">лог сообщений</label>
<br>
<textarea name="messages_log" id="messages_log" cols="30" rows="10" disabled="disabled"></textarea>

		`;
		
		this.game = new CitiesGame();
		
		this.name_input = this.screen.querySelector('#name_input');
		this.name_add = this.screen.querySelector('#name_btn');
		this.name_add.addEventListener('click', () => {
			let name = this.name_input.value.trim();
			if (name.length > 2) this.game.playerEnter(new Player(name));
			this.name_input.value = '';
		});
		
		this.game_start = this.screen.querySelector('#start_game');
		this.game_start.addEventListener('click', () => this.game.play());
		
		this.city_input = this.screen.querySelector('#city_input');
		this.city_send = this.screen.querySelector('#city_send');
		this.city_send.addEventListener('click', () => {
			let city = this.city_input.value.trim();
			this.game.tryGuessCity(city);
			this.city_input.value = '';
		});
		
		this.messages_log = this.screen.querySelector('#messages_log');
		this.game.addEventListener('message', (event) => {
			this.messages_log.innerHTML += `\n > ${event.message}`;
		});
		
		
		this.lastTime = Date.now();
		this.tickBind = this.tick.bind(this);
		this.tick();
	}
	
	tick() {
		let time = Date.now();
		let dt = time - this.lastTime;
		this.game.tick(dt);
		this.lastTime = time;
		requestAnimationFrame(this.tickBind);
	}
}
