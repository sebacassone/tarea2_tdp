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
    // Selecciona el pivote óptimo u
    int u = -1;
    int max = -1;
    // max = max(|P intersec N(v)|) para v en P U X
    for (auto v : *P)
    {
        // P intersec N(v)
        set<int> *neighbours_v = neighbours(v);
        int count = 0;
        // |P intersec N(v)|
        for (auto x : *P)
        {
            // x in P intersec N(v)
            if (neighbours_v->find(x) != neighbours_v->end())
            {
                count++;
            }
        }
        // max(|P intersec N(v)|)
        if (count > max)
        {
            max = count;
            u = v;
        }
        delete neighbours_v;
    }
    // max = max(|P intersec N(v)|) para v en P U X
    for (auto v : *X)
    {
        set<int> *neighbours_v = neighbours(v);
        int count = 0;
        for (auto x : *P)
        {
            if (neighbours_v->find(x) != neighbours_v->end())
            {
                count++;
            }
        }
        if (count > max)
        {
            max = count;
            u = v;
        }
        delete neighbours_v;
    }
    // retorna el pivote óptimo u
    return u;
}

set<set<int> *> *Clique::BK(set<int> *R, set<int> *P, set<int> *X, set<set<int> *> *C)
{
    if (P->empty() && X->empty())
    {
        C->insert(R);
        return (C);
    }

    int u = getOptimalPivot(P, X); // Selecciona el pivote óptimo u

    set<int> *neighbors_u = neighbours(u); // vecinos de u

    set<int> *P_minus_neighbors_u; // P - neighbors(u)
    for (auto x : *P)
    {
        if (neighbors_u->find(x) == neighbors_u->end()) // si x no está en neighbors(u)
        {
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
        C = this->BK(R1, P1, X1, C);

        P_new->erase(v);
        X_new->insert(v);
    }
    return C;
}
