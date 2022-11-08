// Actividad 3.2 Implementación de "Dijkstra and Floyd"
// Estefanía Pérez Yeo - A01639170
// Vanessa Méndez Palacios - A01639925

// Compilación: g++ -std=c++17 *.cpp
// Ejecución: ./a.out < in.txt

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int NO_PARENT = -1;

// O(n)
// función para imprimir el camino más corto de un nodo a otro
void print(int startVertex, vector<int> distances, vector<int> parents) {
  int nVertices = distances.size();

  for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++){
    if (vertexIndex != startVertex) {
      cout << "\nnode " << startVertex + 1 << " to node ";
      cout << vertexIndex + 1  << ": ";
      cout << distances[vertexIndex] << "\t\t";
    }
  }
}

// O(n^3)
void dijkstra(vector<vector<int>> adjacencyMatrix, int startVertex) {
    int nVertices = adjacencyMatrix[0].size();
 
    vector<int> shortestDistances(nVertices);
 
    // added[i] será verdadero si el vértice i es
    // incluido / en el path tree más corto
    // o la distancia más corta desde src a
    // i es finalizada
    vector<bool> added(nVertices);
 
    // Iniciliza todas las distancias como
    // INFINITE y added[] como falso
    for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
      shortestDistances[vertexIndex] = INT_MAX;
      added[vertexIndex] = false;
    }
 
    // distancia del vertex fuente siempre es 0
    shortestDistances[startVertex] = 0;
 
    // arreglo que guarda el camino más corto
    vector<int> parents(nVertices);
 
    // el vertex inicial no tiene parent
    parents[startVertex] = NO_PARENT;

    // encuentra el camino más corto de todos los vertices
    for (int i = 1; i < nVertices; i++) {
      int nearestVertex = -1;
      int shortestDistance = INT_MAX;
      for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
        if (!added[vertexIndex] && shortestDistances[vertexIndex] < shortestDistance) {
          nearestVertex = vertexIndex;
          shortestDistance = shortestDistances[vertexIndex];
        }
      }

      added[nearestVertex] = true;
 
      // Actualiza valor dist de thlose
      // vertices adyacentes del
      // vértice elegido.
      for (int vertexIndex = 0; vertexIndex < nVertices;
        vertexIndex++) {
        int edgeDistance = adjacencyMatrix[nearestVertex][vertexIndex];

        if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortestDistances[vertexIndex])) {
          parents[vertexIndex] = nearestVertex;
          shortestDistances[vertexIndex] = shortestDistance + edgeDistance;
        }
      }
    }
  print(startVertex, shortestDistances, parents);
}

// O(n^3)
int matrixFloyd(int *C, int n, int *A, string* s){
  int i,j,k;
 
  for (i=0; i<n; i++){
    for (j=0; j<n; j++){
      if ( *(C+i*n+j) == -1){
        *(A+i*n+j) = 999999999;
      }else{
        *(A+i*n+j) = *(C+i*n+j);;
        char sz[3]="";
        sprintf(sz,"%d",j+1);
        s[i*n+j]=sz;
      }
    }
  }
 
  
  for (i=0; i<n; i++){
    *(A+i*n+i) = 0;
  }
 
  
  for (k=0; k<n; k++){
    for (i=0; i<n; i++){
      for (j=0; j<n; j++){
        // if(A[i][k] + A[k][j] < A[i][j]){
        if ( *(A+i*n+k) + *(A+k*n+j) < *(A+i*n+j) ){
          // A[i][j] = A[i][k] + A[k][j];
          *(A+i*n+j) = *(A+i*n+k)+ *(A+k*n+j);
        }
      }
    }
  }
 
  return 0;
}


int main() {
  
  int numNodes, input;
  int idx = 0;
  cin >> numNodes;
  
  vector<vector<int>> matrix;
  int* A = new int[numNodes * numNodes];
  string* s = new string[numNodes * numNodes];
  int *C = new int[numNodes * numNodes];


  // Lectura de matriz a usar en Floyd Warshall
  for(int i = 0; i < (numNodes * numNodes); i++){
    cin >> input;
    C[i] = input;
  }

  // Lectura de matriz a usar en Dijkstra
  for (int i = 0; i < numNodes; i++) {
    vector<int> row;
    for (int j = 0; j < numNodes; j++) {
      int num = 0;
      num = C[idx];
      row.push_back(num);
      idx += 1;
    }
    matrix.push_back(row);
  }

  // Dijkstra
  cout << "*********************" << endl;
  cout << "Dijkstra";
  for(int i = 0; i < numNodes; i++){
    dijkstra(matrix,i);
  }

  // Floyd
  cout << endl;
  cout << endl;
  cout << "Floyd" << endl;
  matrixFloyd(C,numNodes,A,s);
  for(int i = 0; i < numNodes; i++){
    for(int j = 0; j < numNodes; j++){
      printf("%d ",*(A + i *numNodes + j));
    }
    printf("\n");
  }
 
  delete [] A;
  delete [] C;
  delete [] s;
  
  return 0;
}
