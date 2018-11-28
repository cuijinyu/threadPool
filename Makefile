CXX = g++
threadPoolTest:threadPool.o task.o main.o
	$(CXX) main.o task.o threadPool.o -g -o threadPoolTest.out -lpthread
task.o:task.cc task.h 
	$(CXX) -c -g -Ddebug task.cc
threadPool.o:threadPool.h threadPool.cc 
	$(CXX) -c -g -Ddebug  threadPool.cc  -lpthread
main.o:main.cc
	$(CXX) -c -g -Ddebug  main.cc
.PHONY:clean
clean:
	-rm *.o
	-rm *.out