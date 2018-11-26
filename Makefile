CXX = g++
threadPoolTest:threadPool.o task.o main.o
	$(CXX) main.o threadPool.o task.o -o threadPoolTest -lpthread
task.o:task.cc task.h
	$(CXX) -c task.cc
threadPool.o:threadPool.cc threadPool.h
	$(CXX) -c threadPool.cc  -lpthread
main.o:main.cc
	$(CXX) -c main.cc
.PHONY:clean
clean:
	-rm *.o
	-rm *.out