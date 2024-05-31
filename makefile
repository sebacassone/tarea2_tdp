all: testClique testMenu main

Clique.o: Clique.cpp Clique.h
	g++ -c -O2 Clique.cpp

testClique: testClique.cpp Clique.o
	g++ -O2 testClique.cpp Clique.o -o testClique

Menu.o: Menu.cpp Menu.h
	g++ -c -O2 Menu.cpp

testMenu: testMenu.cpp Menu.o
	g++ -O2 testMenu.cpp Menu.o -o testMenu

main: main.cpp Clique.o Menu.o
	g++ -O2 main.cpp Clique.o Menu.o -o main

clean:
	rm -f *.o testClique testMenu main
