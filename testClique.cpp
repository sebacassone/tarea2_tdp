#include "Clique.h"

int main()
{

    vector<vector<int>> adyacency = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}};

    Clique c(adyacency, 4);

    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    set<set<int> *> *C = new set<set<int> *>;
    for (int i = 0; i < 4; i++)
    {
        P->insert(i);
    }
    C = c.BK(R, P, X, C);
    for (auto it = C->begin(); it != C->end(); it++)
    {
        for (auto it2 = (*it)->begin(); it2 != (*it)->end(); it2++)
        {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}