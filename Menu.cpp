#include "Menu.h"

/*
    * Method: readGraph
    * Descripción: Leer un archivo con un grafo y convertirlo en una matriz de adyacencia
    * params:
    *  - nombreArchivo: Nombre del archivo con el grafo
    * return:
    *   - Matriz de adyacencia: matriz de adyacencia del grafo

*/
vector<vector<int>> Menu::readGraph(const string &nombreArchivo)
{
    // Abrir el archivo
    ifstream archivo(nombreArchivo);
    if (!archivo)
    {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }
    // Leer el número de nodos
    int numNodos;
    archivo >> numNodos;

    // Inicializar la matriz con ceros
    vector<vector<int>> matriz(numNodos, vector<int>(numNodos, 0));

    // Leer las aristas y asignar 1 en la matriz de adyacencia
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