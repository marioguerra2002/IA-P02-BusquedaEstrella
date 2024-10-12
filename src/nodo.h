#include <iostream>


class Nodo {
  public:
    Nodo(int x, int y, int x_m, int y_m, int coste_punto);
    void set_coste(int coste) { this->coste = coste; }
    void set_coste_acumulado(int coste_estimado_, int coste) { this->coste_acumulado = coste_estimado_ + coste; }
    void set_pared(bool pared) { this->pared = pared; } // en base a true o false se pone el nodo como pared o no
    void set_coste_estimado(int meta_x, int x, int meta_y, int y);
    int get_x() { return x; }
    int get_y() { return y; }
    int get_coste() { return coste; }
    int get_coste_estimado() { return coste_estimado; }
    int get_coste_acumulado() { return coste_acumulado; }
    bool get_pared() { return pared; }
    bool operator < (const Nodo& nodo) const { return coste_acumulado < nodo.coste_acumulado; } // siempre cojo el más pequeño



  private:
    int x; // Coordenada x
    int y; // Coordenada y
    int coste; // Coste de llegar a este nodo g(n)
    int coste_estimado; // Coste estimado de llegar a la meta h(n)
    bool pared = true; // Indica si el nodo es una pared
    int coste_acumulado; // Coste acumulado de llegar a este nodo (fn)
};