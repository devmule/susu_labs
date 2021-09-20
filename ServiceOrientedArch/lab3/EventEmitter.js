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


export default class EventEmitter {
	
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
