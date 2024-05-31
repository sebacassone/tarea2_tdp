#include "Clique.h"

/*
 * Constructor
 * Inicializa la matriz de adyacencia y el tamaño del grafo
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
}

/*
    * Método neighbours
    * Obtiene los vecinos de un vértice
    * params:
    * - v: Vértice
    * return:
    *  - Set con los vecinos del vértice

*/
vector<int> *Clique::neighbours(int v)
{
    auto neighbors = new vector<int>();
    for (int i = 0; i < size; ++i)
    {
        if (adyacency[v][i] == 1)
        {
            neighbors->push_back(i);
        }
    }
    return neighbors;
}

int Clique::choosePivot(vector<int> *P, vector<int> *X)
{
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

        delete neigh_u;
    }

    return pivot;
}

vector<vector<int> *> *Clique::BK(vector<int> *R, vector<int> *P, vector<int> *X, vector<vector<int> *> *C, vector<int> *maxClique)
{
    // Si P y X están vacíos
    if (P->empty() && X->empty())
    {
#pragma omp critical
        {
            C->push_back(new vector<int>(*R));
            // Se guarda el máximo clique
            if (R->size() > maxClique->size())
            {
                maxClique->clear();
                for (int it : *R)
                {
                    maxClique->push_back(it);
                }
            }
        }
        return C;
    }
    // Se escoge un pivote
    int u = choosePivot(P, X);

    // Podar ramificaciones si R + P no es un clique máximo
    if (R->size() + P->size() <= maxClique->size())
    {
        return C;
    }

    // Se recorren los vértices de P
    auto neigh_u = neighbours(u);

    // Se excluyen los vecinos de u
    vector<int> P_excl_neigh_u;
    set_difference(P->begin(), P->end(), neigh_u->begin(), neigh_u->end(), back_inserter(P_excl_neigh_u));

#pragma omp parallel for shared(R, P, X, C, maxClique)
    for (int v : P_excl_neigh_u)
    {
        // Se añade v a R
        if (find(neigh_u->begin(), neigh_u->end(), v) == neigh_u->end())
        {
            // Se crea un nuevo conjunto con R y v
            auto R1 = new vector<int>(*R);
            R1->push_back(v);

            // Se obtienen los vecinos de v y se calcula la intersección con P
            auto vecinos = neighbours(v);
            auto P1 = new vector<int>();
            set_intersection(P->begin(), P->end(), vecinos->begin(), vecinos->end(), back_inserter(*P1));

            // Se calcula la intersección de X y vecinos de v
            auto X1 = new vector<int>();
            set_intersection(X->begin(), X->end(), vecinos->begin(), vecinos->end(), back_inserter(*X1));

            delete vecinos;

            C = BK(R1, P1, X1, C, maxClique);

            delete R1;
            delete P1;
            delete X1;

            // Se elimina v de P y se añade a X
            P->erase(remove(P->begin(), P->end(), v), P->end());
            X->push_back(v);
        }
    }

    delete neigh_u;
    return C;
}