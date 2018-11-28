#ifndef TASK_H
#define TASK_H
#include <iostream>
using std::string;
class Task {
    private:
        string name;
        void *(*func)(void *args);
        void *args;
    public:
        Task (string taskName, void* f(void *args), void * args) {
            name = taskName;
            func = f;
            this -> args = args;
        }
        ~Task () {

        }
        void runFunc() {
            func(args);
        }
};
#endif