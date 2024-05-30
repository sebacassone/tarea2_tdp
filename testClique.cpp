#include "Clique.h"

#include <set>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <iostream>

class Graph
{
public:
    // A map to store the adjacency list of the graph
    std::unordered_map<int, std::set<int>> adjList;

    // Add edge to the graph
    void addEdge(int u, int v)
    {
        adjList[u].insert(v);
        adjList[v].insert(u);
    }

    // Function to get the neighbors of a vertex
    std::set<int> neighbours(int v)
    {
        return adjList[v];
    }

    // Function to find the vertex with the maximum number of connections in P ∩ Neighbors(u)
    int selectPivot(const std::set<int> &P, const std::set<int> &X)
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

    // Function to get the vertex with the highest degree in P
    int selectMaxDegreeVertex(const std::set<int> &P)
    {
        int maxDegree = -1;
        int vertex = -1;
        for (int v : P)
        {
            int degree = adjList[v].size();
            if (degree > maxDegree)
            {
                maxDegree = degree;
                vertex = v;
            }
        }
        return vertex;
    }

    // Function to perform Bron-Kerbosch with pivoting, heuristic selection, and pruning
    std::set<std::set<int>> *BK(std::set<int> *R, std::set<int> *P, std::set<int> *X, std::set<std::set<int>> *C, int maxCliqueSize)
    {
        if (P->empty() && X->empty())
        {
            C->insert(*R);
            maxCliqueSize = std::max(maxCliqueSize, (int)R->size());
            return C;
        }

        int pivot = selectPivot(*P, *X);
        std::set<int> P_without_neighbors;
        std::set_difference(P->begin(), P->end(), adjList[pivot].begin(), adjList[pivot].end(), std::inserter(P_without_neighbors, P_without_neighbors.begin()));

        std::vector<int> P_vec(P_without_neighbors.begin(), P_without_neighbors.end());
        std::sort(P_vec.begin(), P_vec.end(), [this](int a, int b)
                  { return adjList[a].size() > adjList[b].size(); });

        for (int v : P_vec)
        {
            std::set<int> *R1 = new std::set<int>(*R);
            R1->insert(v);

            std::set<int> vecinos = neighbours(v);
            std::set<int> *P1 = new std::set<int>;
            std::set_intersection(P->begin(), P->end(), vecinos.begin(), vecinos.end(), std::inserter(*P1, P1->begin()));

            std::set<int> *X1 = new std::set<int>;
            std::set_intersection(X->begin(), X->end(), vecinos.begin(), vecinos.end(), std::inserter(*X1, X1->begin()));

            if (R1->size() + P1->size() > maxCliqueSize)
            {
                C = this->BK(R1, P1, X1, C, maxCliqueSize);
            }

            P->erase(v);
            X->insert(v);

            delete R1;
            delete P1;
            delete X1;
        }
        return C;
    }
};

int main()
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    std::set<int> R, P = {1, 2, 3, 4}, X;
    std::set<std::set<int>> C;
    g.BK(&R, &P, &X, &C, 0);

    for (const auto &clique : C)
    {
        for (int v : clique)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

// int main()
// {

//     vector<vector<int>> adyacency = {
//         {0, 1, 1, 0},
//         {1, 0, 1, 0},
//         {1, 1, 0, 1},
//         {0, 0, 1, 0}
//     };

//     Clique c(adyacency, 4);

//     set<int> *R = new set<int>;
//     set<int> *P = new set<int>;
//     set<int> *X = new set<int>;
//     set<set<int>*> *C = new set<set<int>*>;
//     for (int i = 0; i < 4; i++) {
//         P->insert(i);
//     }
//     C = c.BK(R, P, X, C);
//     for (auto it = C->begin(); it != C->end(); it++) {
//         for (auto it2 = (*it)->begin(); it2 != (*it)->end(); it2++) {
//             cout << *it2 << " ";
//         }
//         cout << endl;
//     }
//     return 0;
// }