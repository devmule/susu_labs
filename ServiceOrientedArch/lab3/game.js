/**
 * @typedef {Object} ICustomEvent
 * @property {string} type
 * */

/**
 * @typedef {function(event: ICustomEvent)} IEventHandler
 * */

/**
 * @typedef {Object} IEventListener
 * @property {string} type
 * @property {IEventHandler} handler
 * */


class EventEmitter {
	
	constructor() {
		/** @type IEventListener[] */
		this.eventListeners = [];
	}
	
	/**
	 * @param {string} type
	 * @param {IEventHandler} handler
	 * */
	addEventListener(type, handler) {
		this.eventListeners.push({type, handler});
	}
	
	/**
	 * @param {string} type
	 * @param {IEventHandler} handler
	 * */
	removeEventListener(type, handler) {
		
		const filtered = this.eventListeners.filter((eventListener) => {
			return eventListener.type === type && (eventListener.handler === handler || handler == null);
		})
		
		for (let i = 0; i < filtered.length; i++) {
			const index = this.eventListeners.indexOf(filtered[i]);
			this.eventListeners.splice(index, 1);
		}
	}
	
	/**
	 * @param {ICustomEvent} event
	 * */
	dispatchEvent(event) {
		for (let i = 0; i < this.eventListeners.length; i++) {
			const eventListener = this.eventListeners[i];
			if (eventListener.type === event.type) {
				eventListener.handler.call(this, event);
			}
		}
	}
	
	/**
	 * @param {string} type
	 * @return boolean
	 * */
	hasEventListener(type) {
		return !!this.eventListeners.find(el => el.type === type);
	}
}



const TIME_TO_LEFT = 60 * 1000; // 1 минута на отгадывание слова

class Player {
	/** @param {string} name */
	constructor(name) {
		/** @type {string} */
		this.name = name;
	}
}

class CitiesGame extends EventEmitter {
	
	constructor(CITIES) {
		super();
		
		this.CITIES = CITIES;
		
		this.isPlaying = false;
		
		/** @type {Player[]} */
		this.players = [];
		this.curPlayerID = 0;
		this.time = TIME_TO_LEFT;
		
		this.lastLetter = '';
		/** @type {number[]} */
		this.guessedIndices = [];
		
	}
	
	/**
	 * @private
	 * @param {string} given
	 * @return {number}
	 * */
	getCityIndex(given) {
		
		// если первый город был задан и при этом первая буква не совпадает, то сразу отказ
		if ((this.lastLetter !== '') && (given[0].toLowerCase() !== this.lastLetter.toLowerCase())) return -1;
		
		for (let index = 0; index < this.CITIES.length; index++) {
			let city = this.CITIES[index].toLowerCase();
			
			// находим подходящий город
			if (given === city) {
				// если он ещё не отгадан, то отгадываем
				if (this.guessedIndices.indexOf(index) < 0) return index;
				// если он уже отгадан, то отказываем
				else return -1;
			}
		}
		
		// если такого города нет, отказываем
		return -1;
	}
	
	/**
	 * @public
	 * @param {string} city
	 * */
	tryGuessCity(city) {
		if (!this.isPlaying) return;
		
		city = city.trim().toLowerCase();
		let player = this.players[this.curPlayerID];
		
		let cityIndex = this.getCityIndex(city);
		if (cityIndex < 0) {
			
			this.dispatchEvent({
				type: 'message',
				message: `город \"${city}\" не подходит, не существует или уже отгадан`
			});
			
		} else {
			this.guessedIndices.push(cityIndex);
			this.lastLetter = city[city.length - 1].toLowerCase();
			if (["ь", "ъ", "ы"].indexOf(this.lastLetter) >= 0) this.lastLetter = city[city.length - 2].toLowerCase();
			this.time = TIME_TO_LEFT;
			this.curPlayerID = (this.curPlayerID + 1) % this.players.length;
			let current = this.players[this.curPlayerID];
			
			this.dispatchEvent({
				type: 'message', message: `${player.name.trim()} отгадал город \"${city}\", ${current.name.trim()
				} угадывает город на \"${this.lastLetter.toUpperCase()}\".`
			});
		}
		
	}
	
	playerEnter(player) {
		// нельзя подключиться во время игры
		if (this.isPlaying) return;
		
		let index = this.players.indexOf(player);
		if (index >= 0) return;
		
		this.players.push(player);
		
		this.dispatchEvent({type: 'message', message: `${player.name.trim()} присоединился`});
	}
	
	playerExit(player) {
		let index = this.players.indexOf(player);
		if (index < 0) return;
		
		this.players.splice(index, 1);
		this.curPlayerID = this.curPlayerID % this.players.length;
		this.time = TIME_TO_LEFT;
		
		this.dispatchEvent({type: 'message', message: `${player.name.trim()} вышел`});
	}
	
	play() {
		if (this.players.length <= 1 || this.isPlaying) return false;
		this.isPlaying = true;
		this.curPlayerID = 0;
		this.lastLetter = '';
		let player = this.players[this.curPlayerID];
		this.dispatchEvent({type: 'message', message: `Игра началась! ${player.name.trim()} называет любой город!`});
		return true;
	}
	
	/**
	 * @public
	 * @param {number} dt
	 * */
	tick(dt) {
		if (!this.isPlaying) return;
		
		this.time -= dt;
		// console.log(this.time / 1000);
		
		if (this.time < 0) {
			let kicked = this.players[this.curPlayerID];
			
			this.players.splice(this.curPlayerID, 1);
			this.curPlayerID = this.curPlayerID % this.players.length;
			this.time = TIME_TO_LEFT;
			
			let player = this.players[this.curPlayerID];
			
			this.dispatchEvent({type: 'kick', player: kicked});
			this.dispatchEvent({
				type: 'message', message: `${kicked.name.trim()
				} не смог отгадать слово. Слабак. Теперь ${player.name.trim()
				} отгадывает город на \"${this.lastLetter.toUpperCase()}\".`
			});
		}
		
		if (this.players.length === 1) {
			let winner = this.players[0];
			
			this.isPlaying = false;
			this.dispatchEvent({type: 'win', winner: winner});
			this.dispatchEvent({type: 'message', message: `!!! ${winner.name.trim()} ВЫИГРАЛ ИГРУ !!!`});
		}
		
		if (this.players.length === 0) {
			this.isPlaying = false;
		}
	}
	
}

globalThis.Player = Player;
globalThis.CitiesGame = CitiesGame;
