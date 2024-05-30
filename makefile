all: Clique.o testClique

Clique.o: Clique.cpp Clique.h
	g++ -c Clique.cpp

testClique: testClique.cpp Clique.o
	g++ testClique.cpp Clique.o -o testClique

clean:
	rm -f *.o testClique