main: main.o mt19937ar.o
	g++ main.o mt19937ar.o -o main
main.o: main.cpp lib/mt19937ar.h 
	g++ -c main.cpp
mt19937ar.o: lib/mt19937ar.c lib/mt19937ar.h
	g++ -c lib/mt19937ar.c lib/mt19937ar.h
clean:
	rm *.o lib/*.gch
