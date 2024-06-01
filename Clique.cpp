#include "Clique.h"

/*
 * Constructor
 * Inicializa la matriz de adyacencia y el tamaño del grafo, y precalcula los vecinos.
 * params:
 * - a: Matriz de adyacencia
 * - size: Tamaño del grafo
 * return:
 *  - void
 */
Clique::Clique(vector<vector<int>> a, int size)
{
    adyacency = a;
    this->size = size;
    precalculateNeighbors();
}

/*
 * Método precalculateNeighbors
 * Precalcula los vecinos de cada vértice y los almacena en una estructura de datos
 * return:
 *  - void
 */
void Clique::precalculateNeighbors()
{
    neighbors.resize(size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (adyacency[i][j] == 1)
            {
                neighbors[i].push_back(j);
            }
        }
    }
}

/*
 * Método neighbours
 * Obtiene los vecinos precalculados de un vértice
 * params:
 * - v: Vértice
 * return:
 *  - Vector con los vecinos del vértice
 */
vector<int> *Clique::neighbours(int v)
{
    return &neighbors[v];
}

/*
 * Método choosePivot
 * Escoge un pivote para el algoritmo de Bron-Kerbosch
 * params:
 * - P: Conjunto de vértices
 * - X: Conjunto de vértices
 * return:
 *  - Pivote
 */
int Clique::choosePivot(vector<int> *P, vector<int> *X)
{
    // Encuentra el vertice que maximiza la intersección con P, osea el que tiene más vecinos en P
    // Unión de P y X
    vector<int> union_PX;
    set_union(P->begin(), P->end(), X->begin(), X->end(), back_inserter(union_PX));

    // Se inicializan las variables
    int max_intersection_size = -1;
    int pivot = -1;

    // Se recorren los vértices de la unión
    for (int u : union_PX)
    {
        // Se obtienen los vecinos de u
        auto neigh_u = neighbours(u);
        int intersection_size = 0;

        // Se recorren los vértices de P
        for (int v : *P)
        {
            if (find(neigh_u->begin(), neigh_u->end(), v) != neigh_u->end())
            {
                intersection_size++;
            }
        }

        // Se actualiza el pivote
        if (intersection_size > max_intersection_size)
        {
            max_intersection_size = intersection_size;
            pivot = u;
        }
    }

    return pivot;
}

/*
 * Método BK
 * Implementa el algoritmo de Bron-Kerbosch para encontrar cliques en un grafo
 * params:
 * - R: Conjunto de vértices
 * - P: Conjunto de vértices
 * - X: Conjunto de vértices
 * - C: Conjunto de cliques
 * - maxClique: Máximo clique
 * return:
 *  - Conjunto de cliques
 */
void Clique::BK(vector<int> *R, vector<int> *P, vector<int> *X, vector<vector<int> *> *C, vector<int> *maxClique)
{
    // Si P y X están vacíos
    if (P->empty() && X->empty())
    {
#pragma omp critical
        {
            // Mover los elementos de R a un nuevo vector y agregarlo a C
            C->push_back(new vector<int>(*R));
            // Se guarda el máximo clique
            if (R->size() > maxClique->size())
            {
                *maxClique = *R; // Copiar elementos de R a maxClique
            }
        }
        return;
    }

    // Se escoge un pivote
    int u = choosePivot(P, X);

    // Podar ramificaciones si R + P no es un clique máximo
    if (R->size() + P->size() <= maxClique->size())
    {
        return;
    }

    // Se recorren los vértices de P
    auto neigh_u = neighbours(u);

    // Se excluyen los vecinos de u
    vector<int> P_excl_neigh_u;
    set_difference(P->begin(), P->end(), neigh_u->begin(), neigh_u->end(), back_inserter(P_excl_neigh_u));

    // Crear una lista de resultados parciales para evitar la sección crítica
    vector<vector<int> *> local_cliques;

#pragma omp parallel
    {
        vector<int> *local_maxClique = new vector<int>(*maxClique);
        vector<vector<int> *> local_C;

#pragma omp for nowait schedule(dynamic)
        for (int i = 0; i < P_excl_neigh_u.size(); ++i)
        {
            int v = P_excl_neigh_u[i];

            // Se añade v a R
            if (find(neigh_u->begin(), neigh_u->end(), v) == neigh_u->end())
            {
                // Mover los elementos de R a un nuevo vector y agregar v
                auto R1 = new vector<int>(*R);
                R1->push_back(v);

                // Se obtienen los vecinos de v y se calcula la intersección con P
                auto vecinos = neighbours(v);
                vector<int> P1;
                set_intersection(P->begin(), P->end(), vecinos->begin(), vecinos->end(), back_inserter(P1));

                // Se calcula la intersección de X y vecinos de v
                vector<int> X1;
                set_intersection(X->begin(), X->end(), vecinos->begin(), vecinos->end(), back_inserter(X1));

                BK(R1, &P1, &X1, &local_C, local_maxClique);

                delete R1;
            }
        }

#pragma omp critical
        {
            if (local_maxClique->size() > maxClique->size())
            {
                *maxClique = *local_maxClique;
            }
            for (auto clique : local_C)
            {
                C->push_back(clique);
            }
        }

        delete local_maxClique;
    }

    return;
}
