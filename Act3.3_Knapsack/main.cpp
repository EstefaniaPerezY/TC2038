// Actividad 3.3 Implementación de "Knapsack problem"

// Estefanía Pérez Yeo - A01639170
// Vanessa Méndez Palacios - A01639925

// Compilación: g++ -std=c++17 *.cpp
// Ejecución: ./a.out < in.txt

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Función que regresa el valor máximo que puede ponerse en la mochila
// Complejidad: O(N*W)
int knapsack(int maxWeight, int weights[], int vals[], int n) {
	vector<vector<int>> K(n + 1, vector<int>(maxWeight + 1));

	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= maxWeight; j++) {
			if (i == 0 || j == 0)
				K[i][j] = 0;
			else if (weights[i - 1] <= j)
				K[i][j] = ((vals[i - 1] + K[i - 1][j - weights[i - 1]] > K[i - 1][j]) ? vals[i - 1] + K[i - 1][j - weights[i - 1]] : K[i - 1][j]);
			else
				K[i][j] = K[i - 1][j];
		}
	}
	return K[n][maxWeight];
}

int main() {
  int size, val, wt, maxWeight;

  cin >> size;
  
  int vals[size];
  int weights[size];

  for (int i = 0; i < size; i++) {
    cin >> val;
    vals[i] = val;
  }

  for (int i = 0; i < size; i++){
    cin >> wt;
    weights[i] = wt;
  }
  
  cin >> maxWeight;
  
  int n = sizeof(vals) / sizeof(vals[0]);
	
	cout << knapsack(maxWeight, weights, vals, n) << endl;
	
	return 0;
}
