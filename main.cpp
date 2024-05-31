#include "Clique.h"
#include "Menu.h"
#include <chrono> // Para medir el tiempo de ejecución
using namespace std::chrono;

int main()
{
    // Crear un objeto de la clase Menu
    Menu menu;
    vector<int> *R = new vector<int>;
    vector<int> *P = new vector<int>;
    vector<int> *X = new vector<int>;
    vector<int> *maxClique = new vector<int>;
    vector<vector<int> *> *C = new vector<vector<int> *>;
    string nombreArchivo;
    vector<vector<int>> matriz;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    Clique c(vector<vector<int>>(), 0);

    // Hace un menú para leer el archivo y ejecutar el algoritmo
    while (true)
    {
        cout << "Menú" << endl;
        cout << "1. Leer archivo" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opción: ";
        int opcion;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            cout << "Ingrese el nombre del archivo: ";
            cin >> nombreArchivo;

            // Leer el archivo y construir la matriz de adyacencia
            matriz = menu.readGraph(nombreArchivo);
            if (matriz.size() == 0)
            {
                cout << "No se pudo leer el archivo" << endl;
                break;
            }

            // Reiniciar los conjuntos y estructuras de datos
            R->clear();
            P->clear();
            X->clear();
            maxClique->clear();
            C->clear();
            // Se le asigna la matriz de adyacencia a la clase Clique y se inicializa el tamaño
            c = Clique(matriz, matriz.size());

            // Inicializar conjunto P con todos los vértices
            for (int i = 0; i < matriz.size(); i++)
            {
                P->push_back(i);
            }

            // Mide el tiempo
            start = high_resolution_clock::now();

// Llamar a la función paralelizada BK
#pragma omp parallel shared(R, P, X, C, maxClique)
            {
// Iniciar el algoritmo desde el primer vértice
#pragma omp parallel
                {
                    C = c.BK(R, P, X, C, maxClique);
                }
            }

            if (maxClique->size() == 0)
            {
                cout << "No se encontró un máximo clique" << endl;
                break;
            }

            // Se ordena el máximo clique
            sort(maxClique->begin(), maxClique->end());

            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);

            // Solo el máximo clique
            for (auto it = maxClique->begin(); it != maxClique->end(); it++)
            {
                cout << *it << " ";
            }

            // Se imprime el tamaño del máximo clique
            cout << endl
                 << "Tamaño del máximo clique: " << maxClique->size() << endl;

            // Imprime el tamaño del máximo clique
            cout << "Tiempo de ejecución: " << duration.count() << " milisegundos" << endl;

            // Salto de linea
            cout << endl;
            break;
        case 2:
            // Salir
            return 0;
        default:
            cout << "Opción no válida" << endl;
            break;
        }
    }

    return 0;
}