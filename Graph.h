#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

class Graph
{
public:
    void addEdge(int u, int v);
    std::unordered_set<int> neighbours(int v);
    void BK(std::set<int> &R, std::set<int> &P, std::set<int> &X, std::set<std::set<int>> &C, int &maxCliqueSize);
    int selectPivot(const std::set<int> &P, const std::set<int> &X);

private:
    std::unordered_set<int> adjList[100];
};
