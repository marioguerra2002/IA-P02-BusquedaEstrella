#include <iostream>
#include "nodo.h"
#include <vector>
#include <utility>

class MatrizLab {
  public:
    MatrizLab(int**, int filas, int columnas);
    void print_matriz();
    void set_inicio(int x, int y);
    void set_meta(int x, int y);
    std::pair<int, int> get_inicio() { return inicio; }
    std::pair<int, int> get_meta() { return meta; }
    std::vector<std::vector<int>> get_matriz() { return matriz; }

  private:
    int** matriz_emtrada;
    std::pair<int, int> inicio;
    std::pair<int, int> meta;
    Nodo** matriz_nodos;
    int filas_;
    int columnas_;


};