#include "Clique.h"

Clique::Clique(vector<vector<int>> a, int size)
{
    adyacency = a;
    this->size = size;
}

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

int Clique::getOptimalPivot(set<int> *P, set<int> *X)
{
    int pivot = -1;
    int minCommonNeighbors = numeric_limits<int>::max(); // Inicializamos con un valor grande
    for (auto v : *P)
    {
        int commonNeighbors = 0;
        for (auto x : *X)
        {
            if (neighbours(v)->count(x))
            {
                commonNeighbors++;
            }
        }
        if (commonNeighbors < minCommonNeighbors)
        {
            minCommonNeighbors = commonNeighbors;
            pivot = v;
        }
    }
    return pivot;
}

int Clique::getRandomPivot(set<int> *P, set<int> *X)
{
    if (P->empty() && X->empty())
    {
        return -1; // No hay pivote válido si ambos conjuntos están vacíos
    }

    set<int> P_union_X = *P;
    P_union_X.insert(X->begin(), X->end());
    int index = rand() % P_union_X.size();
    auto it = P_union_X.begin();
    advance(it, index);
    return *it;
}

set<set<int> *> *Clique::BK(set<int> *R, set<int> *P, set<int> *X, set<set<int> *> *C)
{
    if (P->empty() && X->empty())
    {
        C->insert(new set<int>(*R));
        return (C);
    }

    int u = getOptimalPivot(P, X); // Selecciona el pivote óptimo u
    if (u == -1)
    {
        return C; // Si no hay pivote válido, retorna el conjunto de cliques encontrado
    }

    set<int> *neighbors_u = neighbours(u); // vecinos de u

    set<int> *P_minus_neighbors_u = new set<int>; // P - neighbors(u)
    for (auto x : *P)
    {
        if (neighbors_u->find(x) == neighbors_u->end())
        { // si x no está en neighbors(u)
            P_minus_neighbors_u->insert(x);
        }
    }

    delete neighbors_u;

    set<int> *P_new = new set<int>(*P_minus_neighbors_u); // esto copia P
    set<int> *X_new = new set<int>(*X);                   // esto copia X

    set<int> *P_iter = new set<int>(*P_minus_neighbors_u);
    for (auto v : *P_iter)
    {
        // R = R U {v}
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        // P = P intersec N(v)
        set<int> *vecinos = this->neighbours(v);
        set<int> *P1 = new set<int>;
        set_intersection(P_new->begin(), P_new->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));

        set<int> *X1 = new set<int>;
        set_intersection(X_new->begin(), X_new->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));

        delete vecinos;

        C = this->BK(R1, P1, X1, C);

        delete R1;
        delete P1;
        delete X1;

        P_new->erase(v);
        X_new->insert(v);
    }
    delete P_minus_neighbors_u;

    return C;
}
