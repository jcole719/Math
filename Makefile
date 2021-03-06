SOURCE = main.o SysofEquations.o Poly.o Vector.o Matrix.o Number.o
CC = g++
CFLAGS = -g -Wall
INCLUDE = -c -I.

all: math

math: $(SOURCE)
	$(CC) $(CFLAGS) -I. $(SOURCE) -o math.exe
	
main.o: main.cpp SysofEquations.h Poly.h Matrix.h Vector.h
	$(CC) $(INCLUDE) main.cpp
	
SysofEquations.o: SysofEquations.cpp SysofEquations.h Number.h
	$(CC) $(INCLUDE) SysofEquations.cpp
	
Poly.o: Poly.cpp Poly.h Vector.h Number.h
	$(CC) $(INCLUDE) Poly.cpp
	
Vector.o: Vector.cpp Vector.h Matrix.h
	$(CC) $(INCLUDE) Vector.cpp
	
Matrix.o: Matrix.cpp Matrix.h Number.h
	$(CC) $(INCLUDE) Matrix.cpp
	
Number.o: Number.cpp Number.h
	$(CC) $(INCLUDE) Number.cpp
	
clean: 
	rm -rf *.o math.exe
