//
// Created by Саид on 08.03.16.
//

#ifndef HTTPSERVER_WORKQUEUE_H
#define HTTPSERVER_WORKQUEUE_H

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

namespace http {
	namespace server {
		typedef struct worker {
			pthread_t thread;
			int terminate;
			struct workqueue *workqueue;
			struct worker *prev;
			struct worker *next;
		} worker_t;
		typedef struct job {
			void (*job_function)(struct job *job);
			void *user_data;
			struct job *prev;
			struct job *next;
		} job_t;
		typedef struct workqueue {
			struct worker *workers;
			struct job *waiting_jobs;
			pthread_mutex_t jobs_mutex;
			pthread_cond_t jobs_cond;
		} workqueue_t;
		int workqueue_init(workqueue_t *workqueue, int numWorkers);
		void workqueue_shutdown(workqueue_t *workqueue);
		void workqueue_add_job(workqueue_t *workqueue, job_t *job);
	}
}


#endif //HTTPSERVER_WORKQUEUE_H
