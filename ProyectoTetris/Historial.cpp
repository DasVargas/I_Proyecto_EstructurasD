#include "Historial.h"
#include <iostream>

using namespace std;

Historial::Historial() {
	inicio = nullptr;
	final = nullptr;
	actual = nullptr;
	replay = nullptr;
}


Historial::~Historial() {
	NodoMovimiento* aux = inicio;
	
	while (aux != nullptr) {
		NodoMovimiento* borrar = aux;
		aux = aux->siguiente;
		delete borrar;
	}
	inicio = nullptr;
	final = nullptr;
	actual = nullptr;
	replay = nullptr;
}


bool Historial::estaVacio() {
	return inicio == nullptr;
}


void Historial::agregar(char movimiento, Pieza& pieza, Tablero& tablero) {
	if (actual != final && actual != nullptr) {
		NodoMovimiento* aux = actual->siguiente;
		while (aux != nullptr) {
			NodoMovimiento* borrar = aux;
			aux = aux->siguiente;
			delete borrar;
		}
		actual->siguiente = nullptr;
		final = actual;
	}
	
	NodoMovimiento* nuevo = new NodoMovimiento;
	
	nuevo->movimiento = movimiento;
	nuevo->tipoPieza = pieza.getTipo();
	nuevo->fila = pieza.getFila();
	nuevo->columna = pieza.getColumna();
	nuevo->orientacion = pieza.getOrientacion();
	
	for (int fila = 0; fila < FILAS; fila++) {
		for (int columna = 0; columna < COLUMNAS; columna++) {
			nuevo->estadoTablero[fila][columna] = tablero.getCelda(fila, columna);
		}
	}
	
	nuevo->anterior = final;
	nuevo->siguiente = nullptr;
	
	if (inicio == nullptr) {
		inicio = nuevo;
	}
	else {
		final->siguiente = nuevo;
	}
	
	final = nuevo;
	actual = nuevo;
}


void Historial::restaurarEstado(NodoMovimiento* nodo, Pieza& pieza, Tablero& tablero) {
	pieza = Pieza(nodo->tipoPieza);
	pieza.setFila(nodo->fila);
	pieza.setColumna(nodo->columna);
	
	while (pieza.getOrientacion() != nodo->orientacion) {
		pieza.rotar();
	}
	
	for (int fila = 0; fila < FILAS; fila++) {
		for (int columna = 0; columna < COLUMNAS; columna++) {
			tablero.setCelda(fila, columna, nodo->estadoTablero[fila][columna]);
		}
	}
}


bool Historial::deshacer(Pieza& pieza, Tablero& tablero) {
	if (actual == nullptr || actual->anterior == nullptr) {
		return false;
	}
	actual = actual->anterior;
	restaurarEstado(actual, pieza, tablero);
	return true;
}


bool Historial::rehacer(Pieza& pieza, Tablero& tablero) {
	if (actual == nullptr || actual->siguiente == nullptr) {
		return false;
	}
	actual = actual->siguiente;
	restaurarEstado(actual, pieza, tablero);
	return true;
}


void Historial::mostrar() {
	NodoMovimiento* aux = inicio;
	while (aux != nullptr) {
		cout << "Movimiento: " << aux->movimiento
		<< " | Pieza: " << aux->tipoPieza
		<< " | Fila: " << aux->fila
		<< " | Columna: " << aux->columna
		<< " | Orientacion: " << aux->orientacion
		<< endl;
		aux = aux->siguiente;
	}
}

void Historial::iniciarReplay(Pieza& pieza, Tablero& tablero) {
	if (inicio == nullptr) {
		return;
	}
	replay = inicio;
	restaurarEstado(replay, pieza, tablero);
}

bool Historial::avanzarReplay(Pieza& pieza, Tablero& tablero) {
	if (replay == nullptr || replay->siguiente == nullptr) {
		return false;
	}
	replay = replay->siguiente;
	
	restaurarEstado(replay, pieza, tablero);
	
	return true;
}
