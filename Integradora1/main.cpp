
/**Actividad Integradora 1
 * Diego Sú Gómez - A01620476
 * Santiago Ortiz Pérez - A01620647
 * Estefanía Pérez Yeo - A01639270

 * Compilación: g++ -std=c++17 *.cpp
 * Ejecución: ./a.out < Prueba.txt (o cualquier archivo de "transmission" tipo txt)
 *
**/

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void substringMasLargo(string transmision1, string transmision2)
{ // Encontrar el substring más largo dentro de los archivos de transmisión. Complejidad Temporal O(n^2)
    int len1 = transmision1.length();
    int len2 = transmision2.length();
    int substringComun[2][max(len1,len2) + 1]; //Crea array para guardar longitudes de substrings con la longitud del string más largo
    int fila, lenSubStr, fin, fin2;
    fila = 0;
    lenSubStr = 0;

    for (int a = 0; a <= len1; a++)
    { // Recorrer cada string
        for (int b = 0; b <= len2; b++)
        {
            if (a == 0 || b == 0)
            {
                substringComun[fila][b] = 0;
            }
            else if (transmision1[a - 1] == transmision2[b - 1])
            {                               // Si hay una coincidencia en el caracter
                substringComun[fila][b] = substringComun[1-fila][b-1] + 1;
                if(substringComun[fila][b] > lenSubStr){
                    lenSubStr = substringComun[fila][b];
                    fin = a-1;
                    fin2 = b-1;
                }
            }
            else
            {
                substringComun[fila][b] = 0;
            }
        }
        fila = 1-fila;
    }

    if (lenSubStr == 0)
    {
        cout << "No hay substring comun entre los archivos de transmision." << endl;
    }
    else
    {
        int indiceInicio = fin - lenSubStr + 1;
        int indiceFin = indiceInicio + lenSubStr - 1;
        int indiceInicio2 = fin2 - lenSubStr + 1;
        int indiceFin2 = indiceInicio2 + lenSubStr - 1;
        cout << "Substring mas largo en comun: " << transmision1.substr(indiceInicio, lenSubStr) << "." << endl;
        cout << "Posicion inicial en transmision1.txt: " << indiceInicio << ". Posicion final en transmision1.txt: " << indiceFin << endl;
        cout << "Posicion inicial en transmision2.txt: " << indiceInicio2 << ". Posicion final en transmision2.txt: " << indiceFin2 << endl;
    }
}

void analizarArchivos(
    string transmision, string mcode, string archivo1,
    string archivo2) { // Analiza si el código malicioso está dentro del archivo
                       // de transmisión. Complejidad Temporal O(n)
  bool encontrado = false;
  mcode.pop_back(); // Eliminar último caracter del string

  for (int i = 0; i < transmision.size() - 1; i++) {
    string substring = transmision.substr(i, mcode.length());
    // cout<<substring<<" "<<mcode<<endl;
    int comparacion = substring.compare(mcode);
    if (comparacion == 0) {
      cout << archivo1 << " contiene codigo de " << archivo2
           << ": True. Posicion de inicio del codigo:  " << i << endl;
      encontrado = true;
    }
    substring = "";
  }

  if (encontrado == false) { // No hubo coincidencias
    cout << archivo1 << " contiene codigo de " << archivo2 << ": False" << endl;
  }
}

string
leerArchivo(string archivo) { // Función para pasar el contenido de un archivo
                              // de texto a un string. Complejidad temporal O(n)
  string filename(archivo);
  char letraC;
  string texto;
  FILE *txt = fopen(filename.c_str(), "r"); // Abre el archivo

  while (!feof(txt)) { // Enviar letras al vector de texto
    letraC = getc(txt);
    texto = texto + letraC;
  }

  fclose(txt);
  return texto;
}

void maxPalindromo(string str) {// Función para encontrar el palíndromo más largo en los archivos de transmisión. Complejidad Temporal O(n^2)
  
  // Almacenar tamaño de string y longitud del palindromo más largo.
  int n = str.size();
  int len_actual = 1;

  //Tabla que representara si el substring de un indice inicial hasta
  //un indice final es palindromo.
  bool pal_mat[n][n];

  //Inicializamos la tabla con valores de 0.
  memset(pal_mat, 0, sizeof(pal_mat));

  //Cualquier substring de 1 caracter es palindromo.
  for (int i = 0; i < n; ++i)
    pal_mat[i][i] = 1;

  // Substring de dos caracteres es palindromo si el caracter pasado y el actual son iguales.
  int inicio = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (str[i] == str[i + 1]) {
      pal_mat[i][i + 1] = 1;
      inicio = i;
      len_actual = 2;
    }
  }

  // Substrings mayores a  2 caracteres revisan si indices anteriores fueron palindromos.
  
  for (int k = 3; k <= n; ++k) {
    // Indice inicial
    for (int i = 0; i < n - k + 1; ++i) {
    
      //Guardar indice final actual
      int j = i + k - 1;

      // Checar si anteriormente parte del substring fue palindromo y si
      //los caracteres en los indices actuales son iguales.
      if (pal_mat[i + 1][j - 1] && str[i] == str[j]) {
        pal_mat[i][j] = true;

        //Si el palindromo es más largo que anteriores se almacena el inicio y su longitud.
        if (k > len_actual) {
          inicio = i;
          len_actual = k;
        }
      }
    }
  }

  //Imprimir substring palindromo más largo
  for (int i = inicio; i <= inicio + len_actual - 1; ++i)
    cout << str[i];

  cout<<endl;
}

int main() {
  string transmision1, transmision2, mc1, mc2, mc3, txtTransmision1,
      txtTransmision2, txtMc1, txtMc2, txtMc3;
  transmision1 = "transmission1.txt";
  transmision2 = "transmission2.txt";
  mc1 = "mcode1.txt";
  mc2 = "mcode2.txt";
  mc3 = "mcode3.txt";
  // Obtener vectores de texto de cada uno de los archivos
  txtTransmision1 = leerArchivo(transmision1);
  txtTransmision2 = leerArchivo(transmision2);
  txtMc1 = leerArchivo(mc1);
  txtMc2 = leerArchivo(mc2);
  txtMc3 = leerArchivo(mc3);

  // Analizar si los MC están dentro de los archivos de transmisión
  analizarArchivos(txtTransmision1, txtMc1, transmision1, mc1);
  analizarArchivos(txtTransmision1, txtMc2, transmision1, mc2);
  analizarArchivos(txtTransmision1, txtMc3, transmision1, mc3);
  analizarArchivos(txtTransmision2, txtMc1, transmision2, mc1);
  analizarArchivos(txtTransmision2, txtMc2, transmision2, mc2);
  analizarArchivos(txtTransmision2, txtMc3, transmision2, mc3);

  // Encontrar el palindromo más largo
  cout << "Palindromo mas largo transimission1.txt: ";
  maxPalindromo(txtTransmision1);
  cout << "Palindromo mas largo transimission2.txt: ";
  maxPalindromo(txtTransmision2);

  // Encuentra el substring común más largo entre ambos archivos
  substringMasLargo(txtTransmision1, txtTransmision2);
}
