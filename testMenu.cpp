#include "Menu.h"

int main()
{
    // Crear un objeto de la clase Menu
    Menu menu;
    vector<vector<int>> matriz = menu.readGraph("archivo.txt");

    // Mostrar la matriz de adyacencia
    cout << "Matriz de adyacencia:" << endl;
    for (const auto &fila : matriz)
    {
        for (int elemento : fila)
        {
            cout << elemento << " ";
        }
        cout << endl;
    }

    return 0;
}