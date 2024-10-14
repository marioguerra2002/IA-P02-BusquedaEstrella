#include <iostream>
#include "nodo.h"
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <iomanip>
#include <sstream>

class MatrizLab {
  public:
    MatrizLab(int**, std::pair<int, int>, std::pair<int, int>, int, int);
    
    void print_matriz_nodos_colores();
    void print_matriz_nodos();
    std::pair<int, int> get_inicio() { return inicio; }
    std::pair<int, int> get_meta() { return meta; }
    void procesar_vecino(int x, int y, int coste_movimiento, Nodo& actual);
    void actualizar_nodo(Nodo& nodo);
    Nodo** get_matriz() { return matriz_nodos; }
    int get_contador_nodos_generados() { return contador_nodos_generados; }
    int get_nodos_cerrados_size() { return nodos_cerrados.size(); }
    std::stringstream matriz_nodos_ss();
    // devuelve el tamaño de los nodos cerrados, que es el número de nodos visitados

  private:
    int** matriz_entrada;
    std::pair<int, int> inicio;
    std::pair<int, int> meta;
    Nodo** matriz_nodos;
    int filas;
    int columnas;
    //std::vector <Nodo> visitados;
    std::priority_queue<Nodo, std::vector<Nodo>, std::greater<Nodo> > visitados;
    std::vector <Nodo> nodos_cerrados;
    int contador_nodos_generados = 0;
};