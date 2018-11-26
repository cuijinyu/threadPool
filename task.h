#ifndef TASK_H
#define TASK_H
#include <iostream>
using std::string;
class Task {
    private:
        string name;
        void * func;
    public:
        Task (string taskName, void * f) {
            name = taskName;
            func = f;
        }
        ~Task () {

        }
};
#endif