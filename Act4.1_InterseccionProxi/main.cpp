// Actividad 4.1 Implementación Intersección y proximidad aplicando geometría computacional
// Estefanía Pérez Yeo - A01639170
// Vanessa Méndez Palacios - A01639925

// Compilación: g++ -std=c++17 *.cpp
// Ejecución: ./a.out < in.txt

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Point {
	int x;
	int y;
};

// Función que determina si un punto se encuentra en un segmento
// Complejidad: O(1)
bool segment(Point p, Point q, Point r) {
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
	  return true;
  }
	return false;
}

// Función que devuelve la orientación de p, q, y r
// Complejidad: O(1)
int orientation(Point p, Point q, Point r) {
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

  // (0) si es colineal
	if (val == 0) {
    return 0;
  }
  
  // (1) si es sentido horario o (2) antihorario
	return (val > 0)? 1: 2;
}

// Función que devuelve True si los dos segmentos de rectas intersecan
// Complejidad: O(1)
bool intersect(Point p1, Point q1, Point p2, Point q2) {
  
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4) {
		return true;
  }

	if (o1 == 0 && segment(p1, p2, q1)) {
    return true;
  }
  
	if (o2 == 0 && segment(p1, q2, q1)) {
    return true;
  }
  
	if (o3 == 0 && segment(p2, p1, q2)) {
    return true;
  }
  
	if (o4 == 0 && segment(p2, q1, q2)) {
    return true;
  }
  
	return false;
}

int main() {
	struct Point p1, q1, p2, q2;

  string x1,y1,x2,y2,x3,y3,x4,y4;
  int i = 1;
  
  while(getline(cin, x1, ',')) {
    p1.x = stoi(x1);
    getline(cin, y1, ',');
    p1.y = stoi(y1);
    getline(cin, x2, ',');
    q1.x = stoi(x2);
    getline(cin, y2, ',');
    q1.y = stoi(y2);
    getline(cin, x3, ',');
    p2.x = stoi(x3);
    getline(cin, y3, ',');
    p2.y = stoi(y3);
    getline(cin, x4, ',');
    q2.x = stoi(x4);
    getline(cin, y4);
    q2.y = stoi(y4);

    // Output
    cout << "Line " << i << " from input: " << "(" << p1.x << "," << p1.y << ") (" << q1.x << "," << q1.y << ") ---- ("<< p2.x << "," << p2.y << ") (" << q2.x << "," << q2.y << ") \n";
    // Llamada a función
    intersect(p1, q1, p2, q2)? cout << "True\n": cout << "False\n";
    i++;
  }
  
	return 0;
}
