#include "Tablero.h"
#include <iostream>

using namespace std;

// Constructor
Tablero::Tablero() {
	cabeza = nullptr;
	crearTablero();
}

// Crear las 20 filas del tablero
void Tablero::crearTablero() {
	
	for (int i = 0; i < FILAS; i++) {
		
		NodoFila* nueva = new NodoFila;
		
		// Inicializar las 10 celdas en 0
		for (int j = 0; j < COLUMNAS; j++) {
			nueva->celdas[j] = 0;
		}
		
		// Insertar la nueva fila al inicio
		nueva->siguiente = cabeza;
		cabeza = nueva;
	}
}

// Mostrar el tablero en consola
void Tablero::mostrarTablero() {
	
	NodoFila* actual = cabeza;
	
	while (actual != nullptr) {
		
		for (int i = 0; i < COLUMNAS; i++) {
			cout << actual->celdas[i] << " ";
		}
		
		cout << endl;
		
		actual = actual->siguiente;
	}
}

// Destructor
Tablero::~Tablero() {
	
	NodoFila* actual = cabeza;
	
	while (actual != nullptr) {
		
		NodoFila* borrar = actual;
		
		actual = actual->siguiente;
		
		delete borrar;
	}
	
	cabeza = nullptr;
}
