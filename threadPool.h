#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <pthread.h>
#include "task.h"
#include <iostream>
#include <vector>

using std::vector;
class ThreadPool {
    private:
        vector <pthread_t> threads;
        vector <Task> tasks;
        int threadNumber;
        static pthread_mutex_t mutex;
        static pthread_cond_t cond;
        static void * runTask(void * taskData);
    public:
        ThreadPool (int number) {
            threadNumber = number;
            createThreads();
        }
        ~ ThreadPool () {

        }
        void createThreads() {
            for (int i = 0; i < threadNumber; i++) {
                pthread_t thread;
                pthread_create(&thread, NULL, runTask, NULL);
            }
        }
};  
#endif