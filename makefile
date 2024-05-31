all: testClique testMenu main

Clique.o: Clique.cpp Clique.h
	g++ -c Clique.cpp

testClique: testClique.cpp Clique.o
	g++ testClique.cpp Clique.o -o testClique

Menu.o: Menu.cpp Menu.h
	g++ -c Menu.cpp

testMenu: testMenu.cpp Menu.o
	g++ testMenu.cpp Menu.o -o testMenu

main: main.cpp Clique.o Menu.o
	g++ main.cpp Clique.o Menu.o -o main

clean:
	rm -f *.o testClique