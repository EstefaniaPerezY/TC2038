#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

// Actividad 2.2 Implementación de "Sufix Array"

// Estefanía Pérez Yeo - A01639170
// Vanessa Méndez Palacios - A01639925

// Compilación: g++ -std=c++17 *.cpp
// Ejecución: ./a.out < in.txt

// Estructura para guardar informacion del suffix
struct suffix{
  int index;
  string suff;
};

// Imprime todos los subtrings
// Time complexity: O(n^3)
vector<string> subString(string s, int n){
  vector<string> vectSubStr; 
  
  for (int i = 0; i < n; i++){
    for (int len = 1; len <= n - i; len++){
      vectSubStr.push_back(s.substr(i, len));
    }
  }

  return vectSubStr;
}

void printVector(vector<string> vect){
  for(int i = 0; i < vect.size(); i++){
    cout << vect[i] << endl;
  }
}

// Función para comparar st1 & st2
int stringCompare(string s1, string s2, int n) {
  int i = 0;
  while (n--) {
    if (s1[i] != s2[i])
      return s1[i] - s2[i];
    i++;
  }
  return 0;
}

// Compara dos strings para acomodarlos
bool compare(suffix suff1, suffix suff2) {
  if (suff1.suff < suff2.suff)
    return true;
  return false;
}

// Complejidad O(n)
// Función creadora del Suffix Array
void suffixArray(string myString, int suffixArr[]) {
  int n = myString.size();
  suffix allSuffix[n]; // guarda todos los suffixes
  vector<string> vectSubStr;

  for (int i = 0; i < n; i++) {
    allSuffix[i].index = i;
    allSuffix[i].suff = myString.substr(i);
  }

  sort(allSuffix, allSuffix + n, compare);
  for (int i = 0; i < n; i++){
    suffixArr[i] = allSuffix[i].index;
  }

  // Print del Suffix Array (idx y sufijo)
  for (int i = 0; i < n; i++){
    cout << allSuffix[i].index << "  " << allSuffix[i].suff << endl;
  }
}

// Complejidad O(n^3)
void suffixArraySearch(string myString, string pattern, int suffixArr[], int array[], int *index) {
  int patLen = pattern.size();
  int strLen = myString.size();
  int left = 0, right = strLen - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    string tempStr = myString.substr(suffixArr[mid]);
    int result = stringCompare(pattern, tempStr, patLen);

    if (result == 0) {
      (*index)++;
      array[(*index)] = suffixArr[mid];
    }

    if (result < 0)
      right = mid - 1;
    else
      left = mid + 1;
  }
}

int main() {
  cout << "-----------------------------------" << endl;
  std::cout << "Implementación de Suffix Array\n";
  cout << endl;
  
  vector<string> vectSubStr;
  string myString, pattern;
  int location[myString.size()];
  int index = -1;
  
  cin >> myString;
  cin >> pattern;

  cout << ">> String: " << myString << endl;
  cout << ">> Pattern: " << pattern << endl;
  
  // Substrings
  vectSubStr = subString(myString, myString.length());
  cout << endl;
  cout << ">> Substrings encontrados:" << endl;
  printVector(vectSubStr);

  // Suffix Array
  cout << endl;
  cout << ">> Suffix Array ordenado:" << endl;
  int suffArr[myString.size()];
  suffixArray(myString, suffArr);

  // Pattern
  suffixArraySearch(myString, pattern, suffArr, location, &index);
  cout << endl;
  for (int i = 0; i <= index; i++) {
    cout << ">> Pattern en posición: " << location[i] << endl;
  }
}
