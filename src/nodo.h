#include <iostream>
#include <utility>


class Nodo {
  public:
    Nodo(int x, int y, int x_m, int y_m, int coste_hasta_punto, int valor);
    // constructor de nodos pared
    Nodo(int x, int y) {
      this->x = x;
      this->y = y;
      coste = 1;
      set_pared();
    }
    Nodo() {};
    void set_coste(int coste) { this->coste = coste; }
    void set_coste_acumulado(int coste_estimado_, int coste) { this->coste_acumulado = coste_estimado_ + coste; }
    void set_pared() { this->pared = pared; } // en base a true o false se pone el nodo como pared o no
    void set_coste_estimado(int meta_x, int x, int meta_y, int y);
    void set_padre(int x, int y) { padre = std::make_pair(x, y); }
    void set_valor(int valor) { this->valor = valor; }
    int get_x() { return x; }
    int get_y() { return y; }
    int get_coste() { return coste; }
    int get_coste_estimado() { return coste_estimado; }
    int get_coste_acumulado() { return coste_acumulado; }
    int get_valor() { return coste; }
    std::pair<int, int> get_padre() { return padre; }
    bool operator < (const Nodo& nodo) const { return coste_acumulado < nodo.coste_acumulado; } // siempre cojo el más pequeño
    bool operator > (const Nodo& nodo) const { return coste_acumulado > nodo.coste_acumulado; }
    bool tiene_padre() const { return padre.first != -1 && padre.second != -1; } // si tiene padre, devuelve true
    void printNodo();
    void operator = (const Nodo& nodo) {
      x = nodo.x;
      y = nodo.y;
      coste = nodo.coste;
      coste_estimado = nodo.coste_estimado;
      coste_acumulado = nodo.coste_acumulado;
      pared = nodo.pared;
    }
    bool operator == (const Nodo& nodo) const {
      return (x == nodo.x && y == nodo.y);
    }
    bool operator != (const Nodo& nodo) const {
      return x != nodo.x || y != nodo.y;
    }



  private:
    int x; // Coordenada x
    int y; // Coordenada y
    int coste; // Coste de llegar a este nodo g(n)
    int coste_estimado; // Coste estimado de llegar a la meta h(n)
    bool pared = false; // Indica si el nodo es una pared
    int coste_acumulado; // Coste acumulado de llegar a este nodo (fn)
    std::pair<int, int> padre; // Coordenadas del nodo padre
    char valor; // valor del nodo
};