CXX=g++
CFLAGS= -Wall
OBJS =  LinkedList.o Heap.o main.o Object.o MSCollector.o
asg1: $(OBJS)
	$(CXX) -g -o asg1 $(OBJS)
LinkedList.o: LinkedList.cpp
	$(CXX) -c LinkedList.cpp $(CFLAGS)
Heap.o: Heap.cpp
	$(CXX) -c Heap.cpp $(CFLAGS)
main.o: main.cpp
	$(CXX) -c main.cpp $(CFLAGS)
Object.o: Object.cpp
	$(CXX) -c Object.cpp $(CFLAGS)
MSCollector.o: MSCollector.cpp
	$(CXX) -c MSCollector.cpp $(CFLAGS)	
clean:
	rm *.o asg1
