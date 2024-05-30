#include "Clique.h"

Clique::Clique(vector<vector<int>> a, int size ) {
    adyacency = a;
    this->size = size;
}

set<int>* Clique::neighbours(int v) {
    set<int>*neibors=new set<int>;
    for (int i = 0; i < size; i++) {
        if (adyacency[v][i] == 1) {
            neibors->insert(i);
        }
    }
    return neibors;
} 

set<set<int>*> * Clique::BK(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C ) {
    if (P->empty() && X->empty()) {
        C->insert(R);
        return(C);
    }

    set<int> *P_new= new set<int>(*P); // esto copia P
    set<int> *X_new= new set<int>(*X); // esto copia X

    set<int> *P_iter = new set<int>(*P);
    for(auto v : *P_iter) {
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int> *vecinos = this->neighbours(v);
        set<int> *P1 = new set<int>;
        set_intersection(P_new->begin(), P_new->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));

        set<int> *X1 = new set<int>;
        set_intersection(X_new->begin(), X_new->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));
        C = this->BK(R1,P1,X1,C);

        P_new->erase(v);
        X_new->insert(v);
    }
    return C;


}
