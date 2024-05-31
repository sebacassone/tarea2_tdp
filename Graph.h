#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <set>

class Graph
{
public:
    // A map to store the adjacency list of the graph
    std::unordered_map<int, std::unordered_set<int>> adjList;
    // Methods
    void addEdge(int u, int v);
    std::unordered_set<int> neighbours(int v);
    int selectPivot(const std::set<int> &P, const std::set<int> &X);
    void BK(std::set<int> &R, std::set<int> &P, std::set<int> &X, std::set<std::set<int>> &C, int &maxCliqueSize);
};
