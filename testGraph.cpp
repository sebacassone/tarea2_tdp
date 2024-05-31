#include "Graph.h"

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
    int maxCliqueSize = 0;
    g.BK(R, P, X, C, maxCliqueSize);

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