#include "matriz_lab.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

int main (int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Error en los argumentos" << std::endl;
    return 1;
  }
  std::ifstream input(argv[1]);
  std::ofstream output(argv[2]);
  if (!input.is_open()) {
    std::cout << "Error al abrir el archivo" << std::endl;
    return 1;
  }
  if (!output.is_open()) {
    std::cout << "Error al abrir el archivo" << std::endl;
    return 1;
  }
  int filas, columnas;
  std::string input_str;
  std::string auxiliar;
  std::vector<std::string> input_vector;
  // las dos primeras lineas son las dimensiones de la matriz
  // coger la matriz
  if (input.is_open()) {
    // std::getline(input, line);
    // std::istringstream iss(line); // para poder leer de un string
    // iss >> auxiliar;
    // filas = std::stoi(auxiliar);
    // // coger siguiente linea que estan las columnas
    // std::getline(input, line);
    // std::istringstream iss2(line);
    // iss2 >> auxiliar;
    // columnas = std::stoi(auxiliar);
    // std::cout << "Filas: " << filas << " Columnas: " << columnas << std::endl;
    while (std::getline(input, auxiliar)) {
      for (unsigned int i = 0; i < auxiliar.size(); i++) { // coge la primera fila
        if (auxiliar[i] != ' ') {
          input_str += auxiliar[i];
        }
      }
      input_vector.push_back(input_str);
      auxiliar.clear();
      input_str.clear();
    }
    
  }
  filas = std::stoi(input_vector[0]);
  columnas = std::stoi(input_vector[1]);
  input_vector.erase(input_vector.begin());
  input_vector.erase(input_vector.begin());
  // se borraron las dos primeras lineas que eran las dimensiones de la matriz

  std::cout << "Filas: " << filas << " Columnas: " << columnas << std::endl;
  // crear matriz de enteros de filas x columnas
  //std::vector<std::vector<int> > matriz;
  int x_meta, y_meta;
  int x_inicio, y_inicio;
  char aux;
  int aux_int;
  int** matriz = new int*[filas];
  for (int i = 0; i < filas; ++i) {
    matriz[i] = new int[columnas];
  }
  
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      aux = input_vector[i][j];
      aux_int = aux - '0';
      if (aux_int == 3) { // inicio
        x_inicio = i;
        y_inicio = j;
      }
      if (aux_int == 4) { // final
        x_meta = i;
        y_meta = j;
      }
      matriz[i][j] = aux - '0';
    }
  }

  std::cout << "Matriz: " << std::endl;
  for (int i = 0; i < filas; ++i) {
    for (int j = 0; j < columnas; ++j) {
      std::cout << matriz[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << "Nodo inicio: " << x_inicio << " " << y_inicio << std::endl;
  std::cout << "Nodo final: " << x_meta << " " << y_meta << std::endl;
  MatrizLab matriz_lab(matriz, std::make_pair(x_inicio, y_inicio), std::make_pair(x_meta, y_meta), filas, columnas);
  return 0;
}