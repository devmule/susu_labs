import {ProcessScheduler} from './ProcessScheduler.js';

export class FCFS extends ProcessScheduler {
	/**
	 * решение процессов по типу FIFO,
	 * невытесняющий, то есть процесс обрабатывается пока не завершится
	 * берёт первый в очереди процесс и обрабатывает его, пока не закончился процесс
	 * @param {number} time - время, отведённое на решение процессов
	 * @return {number} оставшееся время после завершения процесса
	 **/
	process(time = 0) {
		let /*Process*/ job, dt;
		while (time > 0 && this.jobs.length) {
			
			job = this.jobs[0]; // берётся первый в списке
			
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
