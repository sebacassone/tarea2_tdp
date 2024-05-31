#include "Menu.h"

vector<vector<int>> Menu::readGraph(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo)
    {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }

    int numNodos;
    archivo >> numNodos;

    // Inicializar la matriz con ceros
    vector<vector<int>> matriz(numNodos, vector<int>(numNodos, 0));

    int nodoOrigen, nodoDestino;
    while (archivo >> nodoOrigen >> nodoDestino)
    {
        // Ajustar los índices ya que parecen empezar desde 0 en el archivo
        matriz[nodoOrigen][nodoDestino] = 1;
        matriz[nodoDestino][nodoOrigen] = 1; // Si es un grafo no dirigido, también asigna 1 en el otro sentido
    }

    archivo.close();
    return matriz;
}