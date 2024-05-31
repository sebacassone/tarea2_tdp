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
    vector<int> *R = new vector<int>;
    vector<int> *P = new vector<int>;
    vector<int> *X = new vector<int>;
    vector<int> *maxClique = new vector<int>;
    vector<vector<int> *> *C = new vector<vector<int> *>;
    // Inicializar P
    for (int i = 0; i < 4; i++)
    {
        P->push_back(i);
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
    sort(maxClique->begin(), maxClique->end());
    for (auto it = maxClique->begin(); it != maxClique->end(); it++)
    {
        cout << *it << " ";
    }
    return 0;
}