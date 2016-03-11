//
// Created by Саид on 08.03.16.
//


#include "Workqueue.h"

namespace http {
	namespace server {
		#define LL_ADD(item, list) { \
    		item->prev = NULL; \
    		item->next = list; \
    		list = item; \
		}

		#define LL_REMOVE(item, list) { \
    		if (item->prev != NULL) item->prev->next = item->next; \
    		if (item->next != NULL) item->next->prev = item->prev; \
    		if (list == item) list = item->next; \
    		item->prev = item->next = NULL; \
		}
		static void *worker_function(void *ptr) {
			worker_t *worker = (worker_t *) ptr;
			job_t *job;

			while (1) {
				pthread_mutex_lock(&worker->workqueue->jobs_mutex);
				while (worker->workqueue->waiting_jobs == NULL) {
					if (worker->terminate) {
						break;
					}

					pthread_cond_wait(&worker->workqueue->jobs_cond, &worker->workqueue->jobs_mutex);
				}

				if (worker->terminate) {
					break;
				}
				job = worker->workqueue->waiting_jobs;
				if (job != NULL) {
					LL_REMOVE(job, worker->workqueue->waiting_jobs);
				}
				pthread_mutex_unlock(&worker->workqueue->jobs_mutex);
				if (job == NULL) {
					continue;
				}
				job->job_function(job);
			}

			delete worker;
			pthread_exit(NULL);
		}

		Workqueue::Workqueue()
			: workqueue(new workqueue_t)
		{ }

		Workqueue::~Workqueue() {
			delete workqueue;
		}

		int Workqueue::init(int numWorkers) {
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
			pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
			pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;

			if (numWorkers < 1) {
				numWorkers = 1;
			}
			workqueue->jobs_mutex = blank_mutex;
			workqueue->jobs_cond = blank_cond;

			for (int i = 0; i < numWorkers; ++i) {
				worker_t *worker = new worker_t;
				worker->workqueue = workqueue;
				if (pthread_create(&worker->thread, &attr, worker_function, (void *) worker)) {
					std::cerr << "Failed to start all worker threads!" << std::endl;
					delete worker;
					pthread_attr_destroy(&attr);

					return 1;
				}
				LL_ADD(worker, worker->workqueue->workers);
			}
			pthread_attr_destroy(&attr);

			return 0;
		}

		void Workqueue::shutdown() {
			for (worker_t *worker = workqueue->workers; worker != NULL; worker = worker->next) {
				worker->terminate = 1;
			}
			/*pthread_mutex_lock(&workqueue->jobs_mutex);
			workqueue->workers = NULL;
			workqueue->waiting_jobs = NULL;
			pthread_cond_broadcast(&workqueue->jobs_cond);
			pthread_mutex_unlock(&workqueue->jobs_mutex);*/
		}

		void Workqueue::addJob(job_t *job) {
			pthread_mutex_lock(&workqueue->jobs_mutex);
			LL_ADD(job, workqueue->waiting_jobs);
			pthread_cond_signal(&workqueue->jobs_cond);
			pthread_mutex_unlock(&workqueue->jobs_mutex);
		}
	}
}