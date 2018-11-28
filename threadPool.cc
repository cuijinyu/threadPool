#include "threadPool.h"
pthread_mutex_t ThreadPool::mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::cond = PTHREAD_COND_INITIALIZER;

vector<Task> ThreadPool::tasks;

int ThreadPool::threadNumber = 0;
int ThreadPool::maxNumber = 0;

bool ThreadPool::alive = true;

void* ThreadPool::runTask(void * taskData) {
    pthread_t tid = pthread_self();
    while (1) {
        // cout << "test" << endl;
        pthread_mutex_lock(&mutex);

        // 如果队列为空，等待新任务进入队列
        while(tasks.size() == 0 && alive) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (!alive) {
            pthread_mutex_unlock(&mutex);
            // cout << "thread" << tid << "Died" << endl;
            pthread_exit(NULL);
        }

        Task *task;
        vector<Task>::iterator itr = tasks.begin();
        if (itr != tasks.end()) {
            task = &*itr;
            tasks.erase(itr);
        }
        pthread_mutex_unlock(&mutex);
        task -> runFunc();
        // cout << "tid" << tid << "done" << endl;
    }
};

void ThreadPool::addTask(Task *task) {
    pthread_mutex_lock(&mutex);
    tasks.push_back(* task);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
}

bool ThreadPool::kill() {
    if (!alive) {
        return false;
    }
    alive = false;
    for (int i = 0; i < threadNumber; i++) {
        pthread_cond_broadcast(&cond);
        pthread_join(threads[i], NULL);
    }
    delete []threads;
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return true;
}