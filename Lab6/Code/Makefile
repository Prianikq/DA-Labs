CC = g++
OUTPUT = solution
test: bigInteger.o
	$(CC) bigInteger.o benchmark.cpp -o benchmark -lgmp -lgmpxx 
    
all: bigInteger.o
	$(CC) bigInteger.o main.cpp -o $(OUTPUT)

bigInteger.o: bigInteger.hpp bigInteger.cpp
	$(CC) -c bigInteger.cpp

clean:
	rm -f $(OUTPUT) *.o
