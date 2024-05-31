#include "Clique.h"
#include "Menu.h"
#include <chrono>
using namespace std::chrono;

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
    auto start = high_resolution_clock::now();
    C = c.BK(R, P, X, C, maxClique);
    // Calcular el tiempo transcurrido
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    // SOlo el máximo clique
    for (auto it = maxClique->begin(); it != maxClique->end(); it++)
    {
        cout << *it << " ";
    }

    cout << "Tiempo de ejecución: " << duration.count() << " milisegundos" << endl;

    return 0;
}