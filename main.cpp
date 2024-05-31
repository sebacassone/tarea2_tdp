#include "Clique.h"
#include "Menu.h"
#include <omp.h> // Para OpenMP

int main()
{
    Menu menu;
    vector<vector<int>> matriz = menu.readGraph("archivo.txt");

    cout << "Matriz de adyacencia:" << endl;
    for (const auto &fila : matriz)
    {
        for (int elemento : fila)
        {
            cout << elemento << " ";
        }
        cout << endl;
    }

    // Se crea un objeto de la clase Clique
    Clique c(matriz, matriz.size());

    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    set<int> *maxClique = new set<int>;
    set<set<int> *> *C = new set<set<int> *>;
    for (int i = 0; i < matriz.size(); i++)
    {
        P->insert(i);
    }

// Llamar a la función paralelizada BK
#pragma omp parallel shared(R, P, X, C, maxClique)
    {
// Iniciar el algoritmo desde el primer vértice
#pragma omp single nowait
        {
            C = c.BK(R, P, X, C, maxClique);
        }
    }

    // SOlo el máximo clique
    for (auto it = maxClique->begin(); it != maxClique->end(); it++)
    {
        cout << *it << " ";
    }
    return 0;
}