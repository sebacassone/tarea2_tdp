#include "Graph.h"

int main()
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    std::set<int> R, P, X;
    std::set<std::set<int>> C;
    int maxCliqueSize = 0;

    // Initialize P with all vertices in the graph
    for (int i = 1; i <= 4; ++i)
    {
        P.insert(i);
    }

    g.BK(R, P, X, C, maxCliqueSize);

    std::cout << "Maximum Clique Size: " << maxCliqueSize << std::endl;
    for (const auto &clique : C)
    {
        std::cout << "Clique: ";
        for (int v : clique)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
