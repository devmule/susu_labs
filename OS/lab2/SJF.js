import {ProcessScheduler} from './ProcessScheduler.js';

export class SJF extends ProcessScheduler {
	/**
	 * решение процессов по типу Shortest Job First,
	 * невытесняющий, то есть процесс обрабатывается пока не завершится
	 * по завершении обработки предыдущего процесса, берётся самый короткий процесс
	 * @param {number} time - время, отведённое на решение процессов
	 * @param {Array<Process>} jobs - список процессов, необходимых для обработки
	 * @return {number} оставшееся время после завершения процесса
	 **/
	process(time = 0, jobs) {
		let dt;
		while (time > 0 && jobs.length) {
			
			// если процесс не завершен, продолжаем его обрабатывать
			if (!this.job || !jobs.includes(this.job)) { // иначе выбираем самый короткий процесс
				for (let i = 0; i < jobs.length; i++) { // берётся единственный, если всего один, или
					if (!this.job || jobs[i].time < this.job.time) this.job = this.job = jobs[i]; // самый которкий по времени
				}
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
