#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <limits>

using namespace std;

class Clique
{
public:
    vector<vector<int>> adyacency;
    int size;
    Clique(vector<vector<int>> a, int size);
    set<set<int> *> *BK(set<int> *R, set<int> *P, set<int> *X, set<set<int> *> *C);
    set<int> *neighbours(int v);
    int getOptimalPivot(set<int> *P, set<int> *X);
    int getRandomPivot(set<int> *P, set<int> *X);
    int choosePivot(set<int> *P, set<int> *X);
};