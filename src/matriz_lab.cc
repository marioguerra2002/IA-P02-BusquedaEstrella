#include "matriz_lab.h"

MatrizLab::MatrizLab(int** matriz_entrada_, std::pair<int, int> inicio_, std::pair<int, int> meta_, int filas_, int columnas_) {
  matriz_entrada = matriz_entrada_;
  inicio = inicio_;
  meta = meta_;
  filas = filas_;
  columnas = columnas_;
  matriz_nodos = new Nodo*[filas];
  for (int i = 0; i < filas; ++i) {
    matriz_nodos[i] = new Nodo[columnas];
  }
  // Inicializamos la matriz de nodos
  Nodo nodo_inicial(inicio.first, inicio.second, meta.first, meta.second, 0, matriz_entrada[inicio.first][inicio.second]);
  Nodo nodo_meta(meta.first, meta.second, meta.first, meta.second, 0, matriz_entrada[meta.first][meta.second]);
  matriz_nodos[inicio.first][inicio.second] = nodo_inicial;
  
  matriz_nodos[meta.first][meta.second] = nodo_meta;
  
  Nodo actual = nodo_inicial;
  visitados.push_back(actual);
  //visitados_queue.push(actual);
  while (visitados.size() != 0) {
    
    
    actual = visitados[0];
    visitados.erase(visitados.begin());
    if (actual == nodo_meta) {
      std::cout << "Hemos llegado a la meta" << std::endl;
      std::cout << "Camino final: " << std::endl;
      // mostrar nodos cerrados, que son los nodos que hemos visitado
      break;
    }
    nodos_cerrados.push_back(actual);
    //visitados.erase(visitados.begin());
    // vamos a ver los vecinos
    int x = actual.get_x();
    int y = actual.get_y();
    // arriba
    procesar_vecino(x - 1, y, 5, actual);
    
    // abajo
    procesar_vecino(x + 1, y, 5, actual);
    // izquierda
    procesar_vecino(x, y - 1, 5, actual);
    // derecha
    procesar_vecino(x, y + 1, 5, actual);
    // arriba izquierda
    procesar_vecino(x - 1, y - 1, 7, actual);
    // arriba derecha
    procesar_vecino(x - 1, y + 1, 7, actual);
    // abajo izquierda
    procesar_vecino(x + 1, y - 1, 7, actual);
    // abajo derecha
    procesar_vecino(x + 1, y + 1, 7, actual);
    // una vez que hemos procesado los vecinos, añadimos el nodo actual a los nodos cerrados
    // imprimir visitados
    for (unsigned int i = 0; i < visitados.size(); i++) {
      visitados[i].printNodo();
    }
    nodos_cerrados.push_back(actual);
    // mostrar nodos cerrados, que son los nodos que hemos visitado
    // decidir ahora cual es el siguiente nodo a visitar, que es el que tenga el menor coste acumulado (f(n))
    std::sort(visitados.begin(), visitados.end());
    
    
  }
  print_matriz_nodos();
  //imprimir vector de nodos cerrados
  std::cout << "Nodos cerrados: " << std::endl;
  for (unsigned int i = 0; i < nodos_cerrados.size(); i++) {
    nodos_cerrados[i].printNodo();
  }

     
}

void MatrizLab::procesar_vecino (int x, int y, int coste_movimiento, Nodo& actual) {
  if (x >= 0 && x < filas && y >= 0 && y < columnas && matriz_entrada[x][y] != 1) {
    Nodo vecino(x, y, meta.first, meta.second, actual.get_coste() + coste_movimiento, matriz_entrada[x][y]);
    vecino.set_padre(actual.get_x(), actual.get_y());
    actualizar_nodo(vecino);
  } else if (x >= 0 && x < filas && y >= 0 && y < columnas && matriz_entrada[x][y] == 1) {
    Nodo vecino(x, y);
    vecino.set_pared();
    matriz_nodos[x][y] = vecino;
  }
 
}

void MatrizLab::actualizar_nodo(Nodo& nodo) {
  // en caso de que no esté ni en los nodos cerrados ni en los nodos abiertos, lo añadimos a los nodos abiertos (cola de prioridad)
  if (std::find(nodos_cerrados.begin(), nodos_cerrados.end(), nodo) == nodos_cerrados.end() && std::find(visitados.begin(), visitados.end(), nodo) == visitados.end()) {
    visitados.push_back(nodo);
    matriz_nodos[nodo.get_x()][nodo.get_y()] = nodo;
  } else if (std::find(visitados.begin(), visitados.end(), nodo) != visitados.end()) {
    // si ya está en los nodos abiertos, comprobamos si el coste acumulado es menor que el que ya tenía
    for (unsigned int i = 0; i < visitados.size(); i++) {
      if (visitados[i] == nodo) {
        if (nodo.get_coste_acumulado() < visitados[i].get_coste_acumulado()) {
          visitados[i] = nodo;
          matriz_nodos[nodo.get_x()][nodo.get_y()] = nodo;
        }
      }
    }
  }
}
void MatrizLab::print_matriz_nodos() {
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      // si es un nodo, imprime un 0, si es una pared imprime un 1, si es el nodo de inicio imprime un 3, si es el nodo de meta imprime un 4
      if (matriz_nodos[i][j].get_valor() == 1) {
        std::cout << "1";
      } else if (i == inicio.first && j == inicio.second) {
        std::cout << "3";
      } else if (i == meta.first && j == meta.second) {
        std::cout << "4";
      } else {
        std::cout << "0";
      }
    }
    std::cout << std::endl;
  }

}