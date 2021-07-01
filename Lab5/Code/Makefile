CC = g++
FLAGS = -std=c++11 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
OUTPUT = solution
BENCHMARK = benchmark

result: benchmark all

benchmark: tree.o array.o
	$(CC) $(FLAGS) tree.o array.o benchmark.cpp -o $(BENCHMARK)

all: tree.o array.o
	$(CC) $(FLAGS) tree.o array.o main.cpp -o $(OUTPUT)

array.o: structures.hpp array.cpp
	$(CC) $(FLAGS) -c array.cpp
	
tree.o: structures.hpp tree.cpp
	$(CC) $(FLAGS) -c tree.cpp

clean:
	rm -f $(OUTPUT) *.o
