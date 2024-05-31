#ifndef MENU_H
#define MENU_H
#include <fstream> // Include the <fstream> header file
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Menu
{
public:
    // Leer archivo y se convierte en matriz de adyacencia
    vector<vector<int>> readGraph(const string &nombreArchivo);
};
#endif /* MENU_H */