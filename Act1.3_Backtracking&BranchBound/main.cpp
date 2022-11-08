#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

// Actividad 1.3 Implementación de la técnica de programación "backtracking" y "ramificación y poda"

// Estefanía Pérez Yeo A01639270
// Vanessa Méndez Palacios A01639925

// Compilación: g++ -std=c++17 *.cpp
// Ejecución: ./a.out < _nombre_del_archivo.txt

// BACKTRACKING

// Muestra la matriz con la solución
void makePath(int m, int n, int **mazePath) {
  cout << "*********************" << endl;
  cout << "BACKTRACKING SOLUTION" << endl;
  cout << endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      cout << mazePath[i][j] << " ";
    cout << endl;
  }
  cout << endl;
}

// Checa si el siguiente lugar tiene como valor un 1
bool validPlace(int x, int y, int m, int n, int **maze) {
  if (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 1) {
    return true;
  }
  return false;
}

bool solveMaze(int x, int y, int m, int n, int **maze, int **mazePath) {
  // Verifica que se llega a la casilla meta (M-1, N-1)
  if (x == m - 1 && y == n - 1) {
    mazePath[x][y] = 1;
    return true;
  }
// Verifica si la posición es válida
  if (validPlace(x, y, m, n, maze) == true) {
    mazePath[x][y] = 1;
    if (solveMaze(x + 1, y, m, n, maze, mazePath) == true) {
      return true;
    }  
    if (solveMaze(x, y + 1, m, n, maze, mazePath) == true) {
      return true;
    }  
    mazePath[x][y] = 0;
    return false;
  }  
  return false;
}

bool findSolution(int m, int n, int **maze, int **mazePath) {
  if (solveMaze(0, 0, m, n, maze, mazePath) == false) {
    cout << "No hay camino";
    return false;
  }
  makePath(m, n, mazePath);
  return true;
}

// BRANCH AND BOUND
// Muestra el vector solución
void printPath(int m, int n,  vector<vector<int>> &matS) {
  cout << endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      cout << matS[i][j] << " ";
    cout << endl;
  }
  cout << endl;
}

// A Queue Node
struct Node{
  // (x, y) represents matrix cell coordinates, and
  // `dist` represents their minimum distance from the source
  int x, y, dist;
};
 
// Detalla los 4 posibles movimientos a partir de una celda
int row[] = {-1,0,0,1};
int col[] = {0,-1,1,0};
 
// Funcion para checar si es posible ir a la posición (row, col) a
// partir de la posición actual. La funcion retorna falso si (row, col)
// no es una posición válida o tiene el valor de 0 o ya fue viistada.
bool isValid(vector<vector<int>> const &mat,vector<vector<int>> const &matS, vector<vector<bool>> &visited, int row, int col) {
  return (row >= 0 && row < mat.size()) && (col >= 0 && col < mat[0].size())
    && mat[row][col] && !visited[row][col];
}

void mazeSol(int row, int col, vector<vector<int>> &matS, bool indicator){
  if(indicator == true){
    matS[row][col] = 1;
  }else{
    matS[row][col] = 0;
  }
}

// Encuentra la ruta posible más corta en `mat` desde la celda
// (i, j) con destino a (x, y)
int findShortestPathLength(vector<vector<int>> &matS, vector<vector<int>> const &mat, pair<int, int> &src,
                    pair<int, int> &dest){
  // base case: invalid input
  if (mat.size() == 0 || mat[src.first][src.second] == 0 ||
        mat[dest.first][dest.second] == 0) {
      return -1;
  }

  // `M × N` matriz
  int M = mat.size();
  int N = mat[0].size();

  // Construye una matriz `M × N` que lleva el paso de las celdas visitadas
  vector<vector<bool>> visited;
  visited.resize(M, vector<bool>(N));

  // Crea un empty queue
  queue<Node> q;
  
  // Obtiene la celda "source" (i, j)
  int i = src.first;
  int j = src.second;

  // Marca la celda "source" como visitada y en-queue la celda "source"
  visited[i][j] = true;
  q.push({i, j, 0});
  mazeSol(i, j, matS, true); //se comienza a formar la solución

  // Guarda la longitud del camino más largo desde el origen hacia el destino
  int min_dist = INT_MAX;

  // Loop hasta que queue está vacía
  while (!q.empty())
  {
    // dequeue el node frontal y lo procesa
    Node node = q.front();
    q.pop();

    // (i, j) representa la celda actual, y `dist` guarda la
    // distancis mínima desde el origen
    int i = node.x, j = node.y, dist = node.dist;

    // si el destino es encontrado, actualiza `min_dist` y para
    if (i == dest.first && j == dest.second)
    {
        min_dist = dist;
        mazeSol(i, j, matS, true);
        break;
    }
    // Checa por las 4 pisibles movimeintos desde la celda actual
    // y en-queue cada movimiento válido
    for (int k = 0; k < 4; k++)
    {
      // Checa si es posible ir a la posición
      // (i + row[k], j + col[k]) desde la posición actual
      if (isValid(mat,matS, visited, i + row[k], j + col[k]))
      {
        // marcar la siguiente celda como visitada y en-queue it
        visited[i + row[k]][j + col[k]] = true;
        q.push({ i + row[k], j + col[k], dist + 1 });
        mazeSol(i+ row[k],  j+ col[k], matS, true);

      }
    }
  }

  if (min_dist != INT_MAX) {
    return min_dist;
  }

  return -1;
}


int main() {
  //BACKTRACKING
  int m, n;
  int input;

  vector<vector<int>> matS; // Branch & bound - declaracion
  vector<vector<int>> mat; // Branch & bound - declaracion

  cin >> m; // Fila
  cin >> n; // Columna
  
  // Creación de "maze", laberinto del .txt
  int** maze = new int*[m];
  for(int i = 0; i < m; ++i){
    maze[i] = new int[n]; // backtraking
    
  }
  
  // Lectura de maze
  for (int i = 0; i < m; i++) {
    vector<int> row;
    vector<int> blank;
    for (int j = 0; j < n; j++){
      cin >> input;
      maze[i][j] = input; // backtraking
      row.push_back(input);
      blank.push_back(0);
    }
    mat.push_back(row); // b&b
    matS.push_back(blank); // b&b solution
  }

  // Creación de "mazePath", laberinto con respuesta
  int** mazePath = new int*[m];
  for(int i = 0; i < m; ++i){
    mazePath[i] = new int[n];
  }

  findSolution(m, n, maze, mazePath);

  // BRANCH AND BOUND

  // Declaración de origen y destino
  pair<int, int> src = make_pair(0, 0);
  pair<int, int> dest = make_pair(m-1, n-1);
  
  // Encuentra la distancia del camino más corto 
  int min_dist = findShortestPathLength(matS, mat, src, dest);
  
  cout << "************************" << endl;
  cout << "BRANCH & BOUND SOLUTION" << endl;
  
  if (min_dist != -1){
      cout << "The shortest path from source to destination has length " << min_dist + 1<< endl;
    
  }else{
    cout << "Destination cannot be reached from a given source";
  }

  // Muestra el laberinto-solución
  printPath(m, n, matS);
}
