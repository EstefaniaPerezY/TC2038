#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

//Estefanía Pérez Yeo A01639270
//Vanessa Méndez Palacios A01639925

// Compilación: g++ -std=c++17 *.cpp
// Ejecución: ./a.out < _nombre_del_archivo.txt

// Encuentra el cambio a dar partir del precio y billete/moneda dado
int change(int p, int q){
  if(p < q){
    int res = q - p;
    return res;
  }else{
    return -1;
  }
}

// GREEDY -> O(nlogn) + O(total)

// No hay mas de 100 denominaciones
#define max 100
int ansG[max];

// Encuentra el mínimo posible de monedas a dar
int gFindMinCoins(int coins[], int size,  int value){
  int i, count = 0;
  for(i = 0; i < size; i++){
    //take as much from coins[i]
    while(value >= coins[i]){
      //after taking the coin, reduce the value.
      value -= coins[i];
      ansG[count] = coins[i];
      count++;
    }
    if(value == 0){
      break;
    }
  }
  return count;
}

// Mostrar cantidad y denomicación de moneda
void CountPrintG(int size){
  int seen[size];

  for(int i = 0; i < size; i++){
    seen[i] = 0;
  }
    
  // Contador de monedas repetidas en "ansG[]"
  for(int i = 0; i < size; i++) {
    if(seen[i] == 0) {
      int count = 0;
      for(int j = i; j < size; j++){
        if(ansG[j] == ansG[i]){
          count += 1;
          seen[j] = 1;
        }
      }
      cout << "-- " << count << " monedas de $" << ansG[i] << endl;
    }
  }
}

// Ordenamiento de arreglo de mayor a menor
void sortingG(int arr[], int size){
  // Tamaño del arreglo
  int n = size;
  
  sort(arr, arr + n, greater<int>());
}

//DYNAMIC PROGRAMMING -> O(n*c)
// Mantiene un rastro de las monedas exactas a ser utilizadas
vector<int> dpMakeChange(vector<int> coinValueList, int change,vector<int> minCoins, vector<int> coinsUsed){
  
  for (int i = 0; i < change + 1; i++){
    int coinCount = i;
    int newCoin = 1;

    for (int j : coinValueList){
      if (j <= i){
        if (minCoins[i-j] + 1 < coinCount){
          coinCount = minCoins[i-j] + 1; // Asigna el numero (cantidad) de monedas que han sido usadas para hacer la suma. assigns the number of coins that have been used to make the sum.
          newCoin = j; // Asigna la moneda actual que se usará para hacer la suma
        }
      }
    }

    minCoins[i] = coinCount;
    coinsUsed[i] = newCoin;
  }
  return coinsUsed;
}

// Mostrar cantidad y denomicación de moneda
void countPrintD(vector<int> coinsUsed, int size, int change){
  int coin = change;
  vector<int> changeInCoins;

  // Creación de vector solo con las monedas a usar, a partir del vector coinsUsed[]
  while(coin > 0){
    int thisCoin = coinsUsed[coin];
    changeInCoins.push_back(thisCoin);
    coin = coin - thisCoin;
  }
  
  vector<int> seen(size, 0);
    
  // Contador de monedas repetidas en "changeInCoins[]"
  for(int i = 0; i < changeInCoins.size(); i++) {
    if(seen[i] == 0) {
      int count = 0;
      for(int j = i; j < changeInCoins.size(); j++){
        if(changeInCoins[j] == changeInCoins[i]){
          count += 1;
          seen[j] = 1;
        }
      }
      cout << "-- " << count << " monedas de $" << changeInCoins[i] << endl;
    }
  }
  
}


int main() {
  // GREEDY
  
  int size, i, p, q, input;
  // Lectura de total de denominaciones
  cin >> size;
  
  // Arreglo de las denominaciones
  int *denominaciones = new int[size];
  // Vector de denomianciones
  vector<int> denominacionV;
  
  // Lectura de cada denominacion
  for (i = 0; i < size; i++) {
    cin >> input;
    // Greedy
    denominaciones[i] = input;
    // Dynamic
    denominacionV.push_back(input);
  }
  
  // Lectura de precio y billete
  cin >> p;
  cin >> q;

  int value = change(p,q);
  int minCoinsG = gFindMinCoins(denominaciones,size,value);
  sortingG(denominaciones, size);

  // Resultado
  cout << "*****************" << endl;
  cout << "GREEDY" << endl;
  cout << endl;
  cout << "El precio es de $" << p << endl;
  cout << "Se han entregado $" << q << endl;
  cout << "Su cambio es de: $" << value << endl;
  CountPrintG(minCoinsG);
  cout << endl;

  // DYNAMIC PROGRAMMING

  // Vectores a usar en funcion dpMakeChange
  vector<int> minCoins(value + 1, 0);
  vector<int> coinsUsed(value + 1, 0);
  vector<int> coinCount(value + 1, 0);

  // Sort denominaciones de menor a mayor
  sort(denominacionV.begin(), denominacionV.end());
  
  vector<int> coinsU = dpMakeChange(denominacionV, value, minCoins, coinsUsed);
  
  // Resultado
  cout << "*****************" << endl;
  cout << "DYNAMIC" << endl;
  cout << endl;
  cout << "El precio es de $" << p << endl;
  cout << "Se han entregado $" << q << endl;
  cout << "Su cambio es de: $" << value << endl;
  countPrintD(coinsU, size, value);
  cout << endl;
  
  return 0;
}
