all: prog2

prog2: prog2.o
	g++ -g prog2.o -o prog2

prog2.o: prog2.cpp prog2.h
	g++ -c -g prog2.cpp

clean:
	rm -rf *.o
