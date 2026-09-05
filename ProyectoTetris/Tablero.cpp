#include "Tablero.h"
#include <iostream>

using namespace std;

// Constructor
Tablero::Tablero() {
	cabeza = nullptr;
	crearTablero();
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

void Tablero::insertarFilaInicio() {
	NodoFila* nueva = new NodoFila;
	for (int i = 0; i < COLUMNAS; i++) {
		nueva->celdas[i] = 0;
	}
	nueva->siguiente = cabeza;
	cabeza = nueva;
}

bool Tablero::filaCompleta(NodoFila* fila) {
	for (int i = 0; i < COLUMNAS; i++) {
		if (fila->celdas[i] == 0) {
			return false;
		}
	}
	return true;
}

void Tablero::eliminarFila(int posicion) {
	if (cabeza == nullptr) {
		return;
	}
	if (posicion == 0) {
		NodoFila* borrar = cabeza;
		cabeza = cabeza->siguiente;
		delete borrar;
		return;
	}
	NodoFila* actual = cabeza;
	for (int i = 0; i < posicion - 1 && actual != nullptr; i++) {
		actual = actual->siguiente;
	}
	if (actual == nullptr || actual->siguiente == nullptr) {
		return;
	}
	NodoFila* borrar = actual->siguiente;
	actual->siguiente = borrar->siguiente;
	delete borrar;
}
void Tablero::limpiarFilas() {
	NodoFila* actual = cabeza;
	int posicion = 0;
	while (actual != nullptr) {
		if (filaCompleta(actual)) {
			NodoFila* siguiente = actual->siguiente;
			eliminarFila(posicion);
			insertarFilaInicio();
			actual = siguiente;
			posicion++;  
		}
		else {
			actual = actual->siguiente;
			posicion++;
		}
	}
}

void Tablero::llenarFila(int posicion) {
	NodoFila* actual = cabeza;
	for (int i = 0; i < posicion && actual != nullptr; i++) {
		actual = actual->siguiente;
	}
	if (actual == nullptr) {
		return;
	}
	for (int i = 0; i < COLUMNAS; i++) {
		actual->celdas[i] = 1;
	}
}

int Tablero::contarFilas() {
	int contador = 0;
	NodoFila* actual = cabeza;
	while (actual != nullptr) {
		contador++;
		actual = actual->siguiente;
	}
	return contador;
}

int Tablero::getCelda(int fila, int columna) {
	NodoFila* actual = cabeza;
	for (int i = 0; i < fila && actual != nullptr; i++) {
		actual = actual->siguiente;
	}
	if (actual == nullptr) {
		return -1;
	}
	return actual->celdas[columna];
}

void Tablero::setCelda(int fila, int columna, int valor) {
	NodoFila* actual = cabeza;
	for (int i = 0; i < fila && actual != nullptr; i++) {
		actual = actual->siguiente;
	}
	if (actual == nullptr) {
		return;
	}
	actual->celdas[columna] = valor;
}
