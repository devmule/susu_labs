import {ProcessScheduler} from './ProcessScheduler.js';

export class SJFExt extends ProcessScheduler {
	/**
	 * решение процессов по типу Shortest Job First,
	 * вытеснющий, то есть процесс выбирается при добавлении нового
	 * или завершении старого процесса (в целом, обрабатывается всегда самый короткий процесс)
	 * @param {number} time - время, отведённое на решение процессов
	 * @param {Array<Process>} jobs - список процессов, необходимых для обработки
	 * @return {number} оставшееся время после завершения процесса
	 **/
	process(time = 0, jobs) {
		let dt;
		while (time > 0 && jobs.length) {
			
			for (let i = 0; i < jobs.length; i++) { // берётся единственный, если всего один, или
				if (!this.job || jobs[i].time < this.job.time) this.job = jobs[i]; // самый которкий по времени
			}
			
			dt = Math.min(this.job.time, time);
			this.job.time -= dt;
			time -= dt;
			
			if (this.job.time <= 0) { // работа закончилась
				jobs.splice(jobs.indexOf(this.job), 1);
				this.job = null;
			}
		}
		return time;
	}
}
