all: benchmark prog

benchmark: kdtree.o
	g++ kdtree.o benchmark.cpp -o benchmark

prog: kdtree.o
	g++ kdtree.o main.cpp -o prog

kdtree.o: kdtree.cpp kdtree.hpp
	g++ -c kdtree.cpp
clean:
	rm -rf *.o
