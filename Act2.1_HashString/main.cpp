#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <stdio.h>

//Estefanía Pérez Yeo A01639270
//Vanessa Méndez Palacios A01639925

// Complejidad O(n*m)

// Compilacion: g++ -o ./a.out main.cpp
// Ejecucion: ./main
// Cuando salga en consola "nombre de file" ingresar in.txt

// Creacion de tabla con valores DEC de ASCII
std::vector<std::vector<int>> crearTabla(std::queue<int> listaCharInt, int row, int col){
  std::vector<std::vector<int>> table (row, std::vector<int>(col, 0));
  
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      if(listaCharInt.empty() == true){ // si hay espacio "vacios" rellena con el valor de n
        table[i][j] = col;
      }else{
        table[i][j] = listaCharInt.front();
        listaCharInt.pop();
      }
    }
  }
  return table;
}

// Encuentra el numero de filas a ser utilizadas
int numRows(int n, int length){
  int rows;
  int res = length % n; 
  if(res == 0){ // Si sí es multiplo de n
    rows = length / n;
  }else{ // En caso que no sea multiplo de n
    rows = (length / n) + 1;
  }
  return rows;
}

// Convierte cada char en DEC correspondiente a los valores de ASCII
std::queue<int> convertInt(std::string key, int length){
  std::queue<int> listaCharInt;
  int value;
  for(int i = 0; i < length; i++){
    value = (int)key[i];
    listaCharInt.push(value);
  }
  return listaCharInt;
}

// Imprime la tabla
void printTable(std::vector<std::vector<int>> table, int row, int col){
  std::cout << "-----------------------" << std::endl;
  std::cout << "Tabla con valores en DEC:" << std::endl;
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      std::cout << table[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  
}

// Ayuda con la lectura del archivo en formato txt, el cual contiene dos datos: (1) "nombre del archivo" y (2) el valor de "n"
std::pair<std::string,int> readFile(std::string primerArchivo){
  std::ifstream entrada(primerArchivo,std::ios::in);
  std::string line, nameArchivo;
  int n;
  while(entrada){
      entrada >> nameArchivo;
      entrada >> n;
      entrada.close();
  }
  return make_pair(nameArchivo,n);
}

// Crea vector size "n", el cual almacena en cada celda, la suma de cada columna perteneciente a Tabla. Después vect[i] = "(suma_de_columna_i)" % 256
std::vector<int> additionChar(std::vector<std::vector<int>> table, int row, int col){
  std::vector<int> vect{0, col};
  int add;

  // Sumatoria por columna
  for(int i = 0; i < col; i++){
    add = 0;
    for(int j = 0; j < row; j++){
      add += table[j][i];
    }
    vect[i] = add; 
  }

  std::cout << "Valores a[i] :" << std::endl;
  for(int i = 0; i < col; i++){
    std::cout << vect[i] << " "; 
  }
  std::cout << std::endl;
  std::cout << std::endl;

  // % 256
  std::cout << "Valores a[i] % 256:" << std::endl; 
  for(int i = 0; i < col; i++){
    vect[i] = vect[i] % 256;
    std::cout << vect[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  
  return vect;
}

// Almacena en un nuevo vector tipo int, la suma de los elementos en "suma", dependiendo de un indice, es donde se guardará dicha suma, en el nuevo vector "vectN", el cual tiene una medida de n/4
void outTable(std::vector<int> suma, int n){
  std::vector<int> vectN{0,(n/4)}; // creacion de vect
  int idx = 0;
  for(int i = 0; i < n; i++){
    idx = i % (n/4); // actualiza valor de idx
    vectN[idx] += suma[i]; // guarda la suma en vectN
  }

  std::cout << "Valores en HEX:" << std::endl;
  for(int j = 0; j < (n/4); j++){
    std::cout << std::uppercase << std::hex << vectN[j] << " "; // muestra valor en uppercase & en hexadecimal
  }
  std::cout << std::endl;
}

int main(){

  // Declaración de variables a usar
  std::vector<std::vector<int>> table;
  std::queue<int> listaCharInt;
  std::vector<int> addition;
  std::pair<std::string,int> paire;

  // Lectura
  char c;
  std::string filename;
  std::string str = "";
  int cont = 0;

  std::cout << "nombre de file: " << std::endl;
  std::cin >> filename;

  paire = readFile(filename);

  int n = paire.second;
  std::ifstream filee(paire.first, std::ios::in);
 while(filee){
    c = filee.get();
    str = str + c;
    cont++;
  }
  filee.close();
  cont = cont - 1;

  // Encontrar no. de filas necesarias
  int rows = numRows(n, cont);

  // Convertir de Char a DEC
  listaCharInt = convertInt(str, cont);

  // Crear tabla
  table = crearTabla(listaCharInt, rows, n);

  // Muestra la Tabla creada
  printTable(table, rows, n);

  // Sumar todos los valores DEC
  addition = additionChar(table, rows, n);

  // Crea tabla que se muestra como output
  outTable(addition, n);
  
  return 0;
}
