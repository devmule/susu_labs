import {ProcessScheduler, Process} from './ProcessScheduler.js';
import {SJF} from './SJF.js';
import {FCFS} from './FCFS.js';

export class Application {
	constructor() {
		let select = document.getElementById('select-process');
		let processes = [SJF, FCFS];
		this.processes = new Map();
		this.proc /*ProcessScheduler*/ = null;
		
		this.player = null;
		this.pauseBtn = document.getElementById('pause-play-btn');
		
		this.speed = document.getElementById('process-speed');
		this.speed.addEventListener('change', e => this.speed.value = Math.max(1, e.target.value));
		
		this.processesSelector = document.getElementById('select-process');
		this.speed.addEventListener('change', e => this.proc = this.processes.get(e.target.value));
		
		for (let i = 0; i < processes.length; i++) {
			let opt = document.createElement('option');
			let system = processes[i];
			opt.value = system.name;
			opt.innerHTML = system.name;
			this.processes.set(system.name, new system());
			select.appendChild(opt);
			
			if (!this.proc) this.proc = this.processes.get(system.name);
		}
		
		this.tick()
	}
	
	tick() {
		let t = Math.max(1, this.speed.value);
		setTimeout(this.tick.bind(this), 1000 / t);
		this.proc.process(1);
	}
	
	addProcess(options) {
	
	}
}
