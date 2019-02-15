SOURCE = main.o Vector.o Matrix.o Number.o
CC = g++
CFLAGS = -g -Wall
INCLUDE = -c -I.

all: matrix

matrix: $(SOURCE)
	$(CC) $(CFLAGS) -I. $(SOURCE) -o matrix.exe
	
main.o: main.cpp Matrix.h Vector.h
	$(CC) $(INCLUDE) main.cpp
	
Vector.o: Vector.cpp Vector.h Matrix.h Number.h
	$(CC) $(INCLUDE) Vector.cpp
	
Matrix.o: Matrix.cpp Matrix.h Number.h
	$(CC) $(INCLUDE) Matrix.cpp
	
Number.o: Number.cpp Number.h
	$(CC) $(INCLUDE) Number.cpp
	
clean: 
	rm -rf *.o matrix.exe