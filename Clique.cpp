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

int Clique::choosePivot(set<int> *P, set<int> *X)
{
    set<int> union_PX;
    set_union(P->begin(), P->end(), X->begin(), X->end(), inserter(union_PX, union_PX.begin()));

    int max_intersection_size = -1;
    int pivot = -1;

    for (int u : union_PX)
    {
        set<int> *neigh_u = neighbours(u);
        int intersection_size = 0;

        for (int v : *P)
        {
            if (neigh_u->find(v) != neigh_u->end())
            {
                intersection_size++;
            }
        }

        if (intersection_size > max_intersection_size)
        {
            max_intersection_size = intersection_size;
            pivot = u;
        }

        delete neigh_u;
    }

    return pivot;
}

set<set<int> *> *Clique::BK(set<int> *R, set<int> *P, set<int> *X, set<set<int> *> *C, set<int> *maxClique)
{
    if (P->empty() && X->empty())
    {
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

    int u = choosePivot(P, X);

    // Podar ramificaciones si R + P no es un clique máximo
    if (R->size() + P->size() <= maxClique->size())
    {
        return C;
    }

    set<int> *neigh_u = neighbours(u);

    set<int> P_excl_neigh_u;
    set_difference(P->begin(), P->end(), neigh_u->begin(), neigh_u->end(), inserter(P_excl_neigh_u, P_excl_neigh_u.begin()));

    for (auto v : P_excl_neigh_u)
    {
        if (!neighbours(u)->count(v))
        {
            set<int> *R1 = new set<int>(*R);
            R1->insert(v);

            set<int> *vecinos = neighbours(v);
            set<int> *P1 = new set<int>;
            set_intersection(P->begin(), P->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));

            set<int> *X1 = new set<int>;
            set_intersection(X->begin(), X->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));

            delete vecinos;

            C = BK(R1, P1, X1, C, maxClique);

            delete R1;
            delete P1;
            delete X1;

            P->erase(v);
            X->insert(v);
        }
    }

    delete neigh_u;
    return C;
}
