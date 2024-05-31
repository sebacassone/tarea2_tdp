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
set<int> *Clique::neighbours(int v)
{
    set<int> *neibors = new set<int>;
    for (int i = 0; i < size; i++)
    {
        if (adyacency[v][i] == 1)
        {
            neibors->insert(i);
        }
    }
    return neibors;
}

/*
 * Método choosePivot
 * Escoge un pivote
 * params:
 * - P: Conjunto de vértices
 * - X: Conjunto de vértices
 * return:
 *  - Pivote
 */
int Clique::choosePivot(set<int> *P, set<int> *X)
{
    // Unión de P y X
    set<int> union_PX;
    set_union(P->begin(), P->end(), X->begin(), X->end(), inserter(union_PX, union_PX.begin()));

    // Se inicializan las variables
    int max_intersection_size = -1;
    int pivot = -1;

    // Se recorren los vértices de la unión
    for (int u : union_PX)
    {
        // Se obtienen los vecinos de u
        set<int> *neigh_u = neighbours(u);
        int intersection_size = 0;

        // Se recorren los vértices de P
        for (int v : *P)
        {
            if (neigh_u->find(v) != neigh_u->end())
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

/*
 * Método BK
 * Implementa el algoritmo de Bron-Kerbosch
 * params:
 * - R: Conjunto de vértices
 * - P: Conjunto de vértices
 * - X: Conjunto de vértices
 * - C: Conjunto de cliques
 * - maxClique: Máximo clique
 * return:
 *  - Conjunto de cliques
 */
set<set<int> *> *Clique::BK(set<int> *R, set<int> *P, set<int> *X, set<set<int> *> *C, set<int> *maxClique)
{
    // Si P y X están vacíos
    if (P->empty() && X->empty())
    {
#pragma omp critical // Sección crítica
        C->insert(new set<int>(*R));
        // Se guarda el máximo clique
        if (R->size() > maxClique->size())
        {
            maxClique->clear();
            for (auto it = R->begin(); it != R->end(); it++)
            {
                maxClique->insert(*it);
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
    set<int> *neigh_u = neighbours(u);

    // Se excluyen los vecinos de u
    set<int> P_excl_neigh_u;
    set_difference(P->begin(), P->end(), neigh_u->begin(), neigh_u->end(), inserter(P_excl_neigh_u, P_excl_neigh_u.begin()));

#pragma omp parallel for shared(R, P, X, C, maxClique) // Sección paralela
    for (auto v : P_excl_neigh_u)
    {
        // Se añade v a R
        if (!neighbours(u)->count(v))
        {
            // Se crea un nuevo conjunto con R y v
            set<int> *R1 = new set<int>(*R);
            R1->insert(v); // Se añade v a R

            // Se obtienen los vecinos de v y se calcula la intersección con P
            set<int> *vecinos = neighbours(v);
            set<int> *P1 = new set<int>;
            set_intersection(P->begin(), P->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));

            // Se calcula la intersección de X y vecinos de v
            set<int> *X1 = new set<int>;
            set_intersection(X->begin(), X->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));

            delete vecinos;

            C = BK(R1, P1, X1, C, maxClique); // Se llama recursivamente a BK

            delete R1;
            delete P1;
            delete X1;

            // Se elimina v de P y se añade a X
            P->erase(v);
            X->insert(v);
        }
    }

    delete neigh_u;
    return C;
}
