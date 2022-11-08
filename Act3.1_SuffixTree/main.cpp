// Actividad 3.1 Implementación de "Tries"
// Estefanía Pérez Yeo - A01639170
// Vanessa Méndez Palacios - A01639925

// Compilación: g++ -std=c++17 *.cpp
// Ejecución: ./a.out < in.txt ("in" representa el nombre del archivo de entrada tipo txt)

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Tamaño de abecedario
// No toma en cuenta la "ñ"
const int ALPHABET_SIZE = 26;
 
// Trie node
// O(1)
struct TrieNode{
  struct TrieNode *children[ALPHABET_SIZE];

  // isEndOfWord es true si el nodo representa "fin de la palabra"
  bool isEndOfWord;
};

// Retorna nuevo nodo trie (inicializado a NULL)
// O(n)
struct TrieNode *getNode(void){
  struct TrieNode *pNode =  new TrieNode;

  pNode->isEndOfWord = false;

  for (int i = 0; i < ALPHABET_SIZE; i++){
    pNode->children[i] = NULL;
  }

  return pNode;
}
// Sino esta presente, inserta key en el trie,
// Si el key es prefijo del nodo trie, lo marca como leaf node
// O(n)
void insert(struct TrieNode *root, string key){
  struct TrieNode *pCrawl = root;

  for (int i = 0; i < key.length(); i++){
    int index = key[i] - 'a';
    if (!pCrawl->children[index]){
      pCrawl->children[index] = getNode();
    }

    pCrawl = pCrawl->children[index];
  }

  // marca último nodo como leaf node
  pCrawl->isEndOfWord = true;
}

// DFS
// Retorna el recorrido del Trie donde cada nodo es separado por un "|"
// O(n)
string toString(struct TrieNode *root){
  struct TrieNode *pCrawl = root;
  string s = "";
  int size = sizeof(pCrawl->children)/sizeof(pCrawl->children[0]);
  for(int i = 0; i < size; i++){
    if(!pCrawl->children[i]){
      continue;
    }else{
      s += char(i + 'a');
      s += "|";
    }
    s += toString(pCrawl->children[i]);
  }
  return s;
}

// Visualizar recorrido DFS
// O(1)
void printDFS(struct TrieNode *root){
  cout << toString(root) << endl;
}

// retorna true si key está en trie, sino retorna falso
// O(n)
bool search(struct TrieNode *root, string key){
  struct TrieNode *pCrawl = root;

  for (int i = 0; i < key.length(); i++){
    int index = key[i] - 'a';
    if (!pCrawl->children[index]){
      return false;
    }

    pCrawl = pCrawl->children[index];
  }

  return (pCrawl->isEndOfWord);
}

int main(){
  int n = 0;
  int m = 0;
  
  // Lectura
  // Valores a insertar
  cin >> n;
  string keysInsert[n], str;
  for(int i = 0; i < n; i++){
    cin >> str;
    keysInsert[i] = str;
  }
  
  // Valores a buscar
  cin >> m;
  string keysSearch[m];
  for(int i = 0; i < m; i++){
    cin >> str;
    keysSearch[i] = str;
  }
  
  struct TrieNode *root = getNode();

  cout << "***********" << endl;
  cout << endl;
  
  // Trie constructor
  // Insertando strings
  for (int i = 0; i < n; i++){
    insert(root, keysInsert[i]);
  }

  
  // Recorrido DFS
  cout << "--- Recorrido DFS:" << endl;
  printDFS(root);
  cout << endl;

  // Buscar
  cout << "--- ¿Presente en Trie?" << endl;
  for(int i  = 0; i < m; i++){
    cout<< boolalpha << keysSearch[i]<<"->"<<search(root, keysSearch[i])<<endl;
  }
  cout << endl;
  
  return 0;
}
