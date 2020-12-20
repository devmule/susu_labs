import {ProcessScheduler, Process} from './ProcessScheduler.js';
import {SJF} from './SJF.js';
import {FCFS} from './FCFS.js';
import {SJFExt} from "./SJFExt.js";

export class Application {
	constructor() {
		let select = document.getElementById('select-process');
		
		let processes = [SJF, SJFExt, FCFS];
		this.processes = new Map();
		this.currentProcess /*ProcessScheduler*/ = null;
		this.jobs = [];
		
		this.DOMProcessesCache = [];
		this.DOMProcessesScreen = document.getElementById('screen');
		
		this.player = null;
		this.pauseBtn = document.getElementById('pause-play-btn');
		this.pauseBtn.innerHTML = 'запустить';
		this.pauseBtn.addEventListener('click', e => {
			this.pauseBtn.innerHTML = this.player ? 'запустить' : 'пауза';
			this.player = this.player ? clearInterval(this.player) : setInterval(this.tick.bind(this), 100);
		});
		
		this.speed = document.getElementById('process-speed');
		this.speed.addEventListener('change', e => this.speed.value = Math.max(1, e.target.value));
		
		this.processesSelector = document.getElementById('select-process');
		this.processesSelector.addEventListener('change', e => this.currentProcess = this.processes.get(e.target.value));
		
		this.processCreatorFieldTime = document.getElementById('add-process-num');
		this.processCreatorBtnAdd = document.getElementById('add-process-btn');
		this.processCreatorBtnAdd.addEventListener('click', e => {
			this.addProcess(Number(this.processCreatorFieldTime.value));
			this.processCreatorFieldTime.value = '';
		});
		
		for (let i = 0; i < processes.length; i++) {
			let opt = document.createElement('option');
			let system = processes[i];
			opt.value = system.name;
			opt.innerHTML = system.name;
			this.processes.set(system.name, new system());
			select.appendChild(opt);
			
			if (!this.currentProcess) this.currentProcess = this.processes.get(system.name);
		}
	}
	
	createDOMProcessElem() {
		let elem = document.createElement('div');
		elem.classList.add('process-item');
		return elem;
	}
	
	updateVisual() {
		for (let i = 0; i < this.jobs.length; i++) {
			let job = this.jobs[i];
			let elem = this.DOMProcessesCache[i];
			if (!elem) elem = this.DOMProcessesCache[i] = this.createDOMProcessElem();
			this.DOMProcessesScreen.appendChild(elem);
			
			let text = '';
			for (const [key, value] of Object.entries(job)) text += `${key}: ${value}   `;
			elem.innerHTML = `${i + 1}) ${text}`;
		}
		for (let i = this.jobs.length; i < this.DOMProcessesCache.length; i++) {
			let elem = this.DOMProcessesCache[i];
			if (elem.parentNode) elem.parentNode.removeChild(elem);
		}
	}
	
	tick() {
		let time = Number(this.speed.value);
		while (time > 0 && this.jobs.length) {
			time = this.currentProcess.process(time, this.jobs);
		}
		this.updateVisual();
	}
	
	addProcess(time) {
		if (time <= 0) return;
		this.jobs.push(new Process(time));
		this.updateVisual();
	}
}
