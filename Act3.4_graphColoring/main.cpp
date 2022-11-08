// Actividad 3.4 Implementación de "Graph coloring"
// Estefanía Pérez Yeo - A01639170
// Vanessa Méndez Palacios - A01639925

// Compilación: g++ -std=c++17 *.cpp
// Ejecución: ./a.out < in.txt

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Función que determina si es posible asignar color a los nodos
bool safeColoring(vector<vector<int>> matrix, int n, int c, int color[], int N) {
  for (int i = 0; i < N; i++) {
    if (matrix[n][i] && (c == color[i])) {
      return false;
    }
  }
  return true; 
}

// Función que asigna color a los nodos
bool graphColoring(vector<vector<int>> matrix, int numColors, int n, int color[], int N) {
  if (n == N) {
    return true;
  }
  for (int i = 0; i <= numColors; i++) {
    if (safeColoring(matrix, n, i, color, N)) {
      color[n] = i;
      if (graphColoring(matrix, numColors, n + 1, color, N)) {
        return true;
      }
      color[n] = 0;
    }
  }
  return false;
}

// Función para imprimir los colores asignados a cada nodo
void printcolours(int color[], int N) {
  for (int i = 0; i < N - 1; i++) {
    cout << "Node " << i << ", Assigned Color: " << color[i] << endl;
  }
}

int main() {
  // Declaración de variables
  int N, num;
  int numColors = 4;
  cin >> N;
  int color[N];
  vector<vector<int>> matrix;

  // Lectura de matriz
  for (int i = 0; i < N; i++) {
    vector<int> row;
    for (int j = 0; j < N; j++) {
      cin >> num;
      row.push_back(num);
    }
    matrix.push_back(row);
  }
  
  memset(color, 0, sizeof color);
  
  bool flag = graphColoring(matrix, numColors, 0, color, N);
  
  if (flag) {
    printcolours(color, N);
  }
  else {
    cout << "No es posible asignar colores a los nodos" << endl;;    
  }
  
  return 0;
}
