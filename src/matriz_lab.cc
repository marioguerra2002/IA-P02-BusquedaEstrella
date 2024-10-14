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
  nodo_inicial.set_padre(-1, -1);
  contador_nodos_generados++;
  // imprimir padre de nodo inicial
  Nodo nodo_meta(meta.first, meta.second, meta.first, meta.second, 0, matriz_entrada[meta.first][meta.second]);
  matriz_nodos[inicio.first][inicio.second] = nodo_inicial;
  
  matriz_nodos[meta.first][meta.second] = nodo_meta;
  

  visitados.push(nodo_inicial);
  //visitados_queue.push(actual);
  while (!visitados.empty()) {
    Nodo actual = visitados.top();
    // el nodo que vamos a visitar es el que tenga el menor coste acumulado, pero tiene 
    // que ser conexo al nodo anterior

    visitados.pop();
    if (actual == nodo_meta) {
      std::cout << "Hemos llegado a la meta" << std::endl;
      print_matriz_nodos();
      print_matriz_nodos_colores();
      
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
    
  }
  // en caso de que no haya camino
  if (visitados.empty()) {
    std::cout << "No hay camino" << std::endl;
    return;
  }

  
  
  //imprimir vector de nodos cerrados

     
}

void MatrizLab::procesar_vecino (int x, int y, int coste_movimiento, Nodo& actual) {
  if (x >= 0 && x < filas && y >= 0 && y < columnas && matriz_entrada[x][y] != 1) {
    Nodo vecino(x, y, meta.first, meta.second, actual.get_coste() + coste_movimiento, matriz_entrada[x][y]);
    vecino.set_padre(actual.get_x(), actual.get_y());
    contador_nodos_generados++;
    actualizar_nodo(vecino);
  } else if (x >= 0 && x < filas && y >= 0 && y < columnas && matriz_entrada[x][y] == 1) {
    Nodo vecino(x, y);
    vecino.set_pared();
    matriz_nodos[x][y] = vecino;
  }
 
}

void MatrizLab::actualizar_nodo(Nodo& nodo) {
  // en caso de que no esté ni en los nodos cerrados ni en los nodos abiertos, lo añadimos a los nodos abiertos (cola de prioridad)
  if (std::find(nodos_cerrados.begin(), nodos_cerrados.end(), nodo) == nodos_cerrados.end()) {
    bool nodo_encontrado = false;
    std::vector<Nodo> nuevos_visitados;
    while (!visitados.empty()) {
      Nodo top_nodo = visitados.top();
      visitados.pop();
      if (top_nodo == nodo) {
        nodo_encontrado = true;
        if (nodo.get_coste_acumulado() < top_nodo.get_coste_acumulado()) {
          top_nodo = nodo; // actualizamos el nodo con el nuevo coste acumulado y el nuevo padre
        }
      }
      nuevos_visitados.push_back(top_nodo);
    }
    for (auto& nodo_actualizado : nuevos_visitados) {
      visitados.push(nodo_actualizado);
    }
    if (!nodo_encontrado) {
      visitados.push(nodo);
    }
    matriz_nodos[nodo.get_x()][nodo.get_y()] = nodo;
  }
}
// si el nodo esta en los nodos cerrados, se imprime un *
void MatrizLab::print_matriz_nodos_colores() {
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (matriz_entrada[i][j] == 1) {
        std::cout << "\033[40m  \033[0m";  // Black square (wall)
      } else if (i == inicio.first && j == inicio.second) {
        std::cout << "\033[42m  \033[0m";  // Green square (start)
      } else if (i == meta.first && j == meta.second) {
        std::cout << "\033[41m  \033[0m";  // Red square (goal)
      } else if (std::find(nodos_cerrados.begin(), nodos_cerrados.end(), matriz_nodos[i][j]) != nodos_cerrados.end()) {
        std::cout << "\033[44m  \033[0m";  // Blue square (visited path)
      } else {
        std::cout << "\033[47m  \033[0m";  // White square (empty)
      }
    }
    std::cout << std::endl;
  }
}

void MatrizLab::print_matriz_nodos() {
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      // si es un nodo, imprime un 0, si es una pared imprime un 1, si es el nodo de inicio imprime un 3, si es el nodo de meta imprime un 4
      // comprobar si nodo está en nodos cerrados
      // voy a recorrer con la matriz de entrada (ya que tiene todos los valores)
      if (matriz_entrada[i][j] == 0) {
        if (std::find(nodos_cerrados.begin(), nodos_cerrados.end(), matriz_nodos[i][j]) != nodos_cerrados.end()) {
          std::cout << "*";
        } else {
          std::cout << "0";
        }
      } else if (matriz_entrada[i][j] == 1) {
        std::cout << "1";
      } else if (matriz_entrada[i][j] == 3) {
        std::cout << "3";
      } else if (matriz_entrada[i][j] == 4) {
        std::cout << "4";
      }
    }
    std::cout << std::endl;
  }
}

std::stringstream MatrizLab::matriz_nodos_ss() {
  std::stringstream ss;
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      // si es un nodo, imprime un 0, si es una pared imprime un 1, si es el nodo de inicio imprime un 3, si es el nodo de meta imprime un 4
      // comprobar si nodo está en nodos cerrados
      // voy a recorrer con la matriz de entrada (ya que tiene todos los valores)
      if (matriz_entrada[i][j] == 0) {
        if (std::find(nodos_cerrados.begin(), nodos_cerrados.end(), matriz_nodos[i][j]) != nodos_cerrados.end()) {
          ss << "*";
        } else {
          ss << "0";
        }
      } else if (matriz_entrada[i][j] == 1) {
        ss << "1";
      } else if (matriz_entrada[i][j] == 3) {
        ss << "3";
      } else if (matriz_entrada[i][j] == 4) {
        ss << "4";
      }
    }
    ss << std::endl;
  }
  return ss;
}





