#include <fstream> // Include the <fstream> header file
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Menu
{
public:
    int size;
    // Leer archivo y se convierte en matriz de adyacencia
    vector<vector<int>> readGraph(const string &nombreArchivo);
};