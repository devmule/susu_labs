import {ProcessScheduler} from './ProcessScheduler.js';

export class SJF extends ProcessScheduler {
	/**
	 * решение процессов по типу Shortest Job First,
	 * невытесняющий, то есть процесс обрабатывается пока не завершится
	 * по завершении обработки предыдущего процесса, берётся самый короткий процесс
	 * @param {number} time - время, отведённое на решение процессов
	 * @return {number} оставшееся время после завершения процесса
	 **/
	process(time = 0) {
		let /*Process*/ job, dt;
		while (time > 0 && this.jobs.length) {
			
			// берётся самый которкий по времени или единственный, если всего один
			job = this.jobs.reduce((selected, curr) => !selected ? curr : // берётся единственный, если всего один, или
				selected.time > curr.time ? curr : selected); // самый которкий по времени
			
			dt = Math.min(job.time, time);
			job.time -= dt;
			time -= dt;
			
			if (job.time <= 0) { // работа закончилась
				this.jobs.shift();
			}
		}
		return time;
	}
}
