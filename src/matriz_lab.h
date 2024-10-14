#include <iostream>
#include "nodo.h"
#include <vector>
#include <utility>
#include <set>
#include <queue>

class MatrizLab {
  public:
    MatrizLab(int**, std::pair<int, int>, std::pair<int, int>, int, int);
    
    void print_matriz_nodos();
    void set_inicio(int x, int y);
    void set_meta(int x, int y);
    std::pair<int, int> get_inicio() { return inicio; }
    std::pair<int, int> get_meta() { return meta; }
    void procesar_vecino(int x, int y, int coste_movimiento, Nodo& actual);
    void actualizar_nodo(Nodo& nodo);
    Nodo** get_matriz() { return matriz_nodos; }

  private:
    int** matriz_entrada;
    std::pair<int, int> inicio;
    std::pair<int, int> meta;
    Nodo** matriz_nodos;
    int filas;
    int columnas;
    std::vector<std::pair<int,int> > vecinos;
    std::vector<std::pair<int,int> > camino_final;
    std::vector <Nodo> visitados;
    std::priority_queue<Nodo, std::vector<Nodo>, std::greater<Nodo> > visitados_queue;
    std::vector <Nodo> nodos_cerrados;



};