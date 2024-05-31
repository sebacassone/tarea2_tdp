#ifndef CLIQUE_H
#define CLIQUE_H
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <limits>
#include <omp.h> // Para OpenMP

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
    vector<vector<int> *> *BK(vector<int> *R, vector<int> *P, vector<int> *X, vector<vector<int> *> *C, vector<int> *maxClique);
    // Encontrar vecinos de un vértice
    vector<int> *neighbours(int v);
    // Elegir pivote
    int choosePivot(vector<int> *P, vector<int> *X);

private:
    // Atributos
    vector<vector<int>> adyacency;
    int size;
};
#endif /* Clique_h */