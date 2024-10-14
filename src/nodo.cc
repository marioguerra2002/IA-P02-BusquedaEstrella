#include "nodo.h"



Nodo::Nodo (int x_, int y_, int x_m, int y_m, int coste_hasta_punto, int valor_) {
  // x_m y y_m son las coordenadas donde está la meta
  x = x_;
  y = y_;
  coste = coste_hasta_punto;
  if (valor_ == 1) {
    set_pared();
    return;
    // en caso de que sea una pared, no hace falta calcular.
  } else {
    valor = valor_;
  }
  set_coste_estimado(x_, y_, x_m, y_m);
  set_coste_acumulado(coste_estimado, coste);
}

void Nodo::set_coste_estimado(int x, int y, int meta_x, int meta_y) {
  coste_estimado = (abs(meta_x - x) + abs(meta_y - y)) * 3; // abs devuelve el valor absoluto
}

void Nodo::printNodo() {
  std::cout << "X: " << x << ", Y: " << y << std::endl;
  std::cout << "g(n): " << coste;
  std::cout << "  h(n): " << coste_estimado;
  std::cout << "  f(n): " << coste_acumulado << std::endl;
}

