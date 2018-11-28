#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <pthread.h>
#include "task.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
class ThreadPool {
    private:
        pthread_t * threads;
        static vector <Task> tasks;
        static int threadNumber;
        static int maxNumber;
        static bool alive;
        static pthread_mutex_t mutex;
        static pthread_cond_t cond;
        static void * runTask(void * taskData);
    public:
        ThreadPool (int number, int maxNumber) {
            alive = true;
            threadNumber = number;
            maxNumber = maxNumber;
            createThreads();
        }
        ~ ThreadPool () {
            // kill();
        }
        void createThreads() {
            threads = new pthread_t[threadNumber];
            for (int i = 0; i < threadNumber; i++) {
                pthread_create(&threads[i], NULL, runTask, NULL);
            }
            return;
        }
        void addTask(Task * task);
        bool kill();
        bool getTasksSize() {
            // cout << tasks.empty() << endl; 
            return tasks.empty();
        }
        bool getAlive() {
            return alive;
        }
};  
#endif