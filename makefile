all: Clique.o testClique

Clique.o: Clique.cpp Clique.h
	g++ -c Clique.cpp

testClique: testClique.cpp Clique.o
	g++ testClique.cpp Clique.o -o testClique

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp

testGraph: testGraph.cpp Graph.o
	g++ testGraph.cpp Graph.o -o testGraph

clean:
	rm -f *.o testClique testGraph