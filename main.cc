#include "threadPool.h"
#include "task.h"
#include <iostream>
void *echo(void *args) {
    cout << "try" << endl;
}
int main () {
    ThreadPool *pool = new ThreadPool(4, 10);
    Task test("test", echo, (void *)"123");
    Task test1("test", echo, (void *)"123");
    pool -> addTask(&test);
    pool -> addTask(&test1);
    while(1) {
        if (pool -> getTasksSize()) {
            if (!pool -> kill()) {
                exit(0);
            }
            return 0;
        }
    }
    return 0;
}