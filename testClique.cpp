#include "Clique.h"

int main()
{
    // Matriz de adyacencia
    vector<vector<int>> adyacency = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}};

    Clique c(adyacency, 4); // Crear un objeto de la clase Clique

    // Conjuntos
    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    set<int> *maxClique = new set<int>;
    set<set<int> *> *C = new set<set<int> *>;
    // Inicializar P
    for (int i = 0; i < 4; i++)
    {
        P->insert(i);
    }
    // Llamar a la función paralelizada BK
#pragma omp parallel shared(R, P, X, C, maxClique)
    {
// Iniciar el algoritmo desde el primer vértice
#pragma omp single nowait
        {
            C = c.BK(R, P, X, C, maxClique);
        }
    }
    for (auto it = maxClique->begin(); it != maxClique->end(); it++)
    {
        cout << *it << " ";
    }
    return 0;
}