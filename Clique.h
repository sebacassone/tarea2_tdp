#ifndef CLIQUE_H
#define CLIQUE_H
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <limits>

using namespace std;

/*
 * Clase Clique
 * Implementa el algoritmo de Bron-Kerbosch para encontrar cliques en un grafo
 * Se utiliza la matriz de adyacencia para representar el grafo
 */
class Clique
{
public:
    // Métodos
    // Constructor
    Clique(vector<vector<int>> a, int size);
    // Algoritmo de Bron-Kerbosch
    set<set<int> *> *BK(set<int> *R, set<int> *P, set<int> *X, set<set<int> *> *C, set<int> *maxClique);
    // Obtiene los vecinos de un vértice
    set<int> *neighbours(int v);
    // Escoge un pivote
    int choosePivot(set<int> *P, set<int> *X);

private:
    // Atributos
    vector<vector<int>> adyacency;
    int size;
};
#endif /* Clique_h */