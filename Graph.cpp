#include "Graph.h"

void Graph::addEdge(int u, int v)
{
    adjList[u].insert(v);
    adjList[v].insert(u);
}

std::unordered_set<int> Graph::neighbours(int v)
{
    return adjList[v];
}

int Graph::selectPivot(const std::set<int> &P, const std::set<int> &X)
{
    std::set<int> unionPX;
    std::set_union(P.begin(), P.end(), X.begin(), X.end(), std::inserter(unionPX, unionPX.begin()));

    int maxConnections = -1;
    int pivot = -1;
    for (int u : unionPX)
    {
        int connections = 0;
        for (int v : P)
        {
            if (adjList[u].count(v))
            {
                connections++;
            }
        }
        if (connections > maxConnections)
        {
            maxConnections = connections;
            pivot = u;
        }
    }
    return pivot;
}

void Graph::BK(std::set<int> &R, std::set<int> &P, std::set<int> &X, std::set<std::set<int>> &C, int &maxCliqueSize)
{
    if (P.empty() && X.empty())
    {
        C.insert(R);
        maxCliqueSize = std::max(maxCliqueSize, static_cast<int>(R.size()));
        return;
    }

    int pivot = selectPivot(P, X);
    std::set<int> P_without_neighbors;
    std::set_difference(P.begin(), P.end(), adjList[pivot].begin(), adjList[pivot].end(), std::inserter(P_without_neighbors, P_without_neighbors.begin()));

    std::vector<int> P_vec(P_without_neighbors.begin(), P_without_neighbors.end());
    std::sort(P_vec.begin(), P_vec.end(), [this](int a, int b)
              { return adjList[a].size() > adjList[b].size(); });

    for (int v : P_vec)
    {
        R.insert(v);
        std::unordered_set<int> vecinos = neighbours(v);
        std::set<int> P1, X1;
        std::set_intersection(P.begin(), P.end(), vecinos.begin(), vecinos.end(), std::inserter(P1, P1.begin()));
        std::set_intersection(X.begin(), X.end(), vecinos.begin(), vecinos.end(), std::inserter(X1, X1.begin()));

        if (R.size() + P1.size() > maxCliqueSize)
        {
            BK(R, P1, X1, C, maxCliqueSize);
        }

        R.erase(v);
        P.erase(v);
        X.insert(v);
    }
}