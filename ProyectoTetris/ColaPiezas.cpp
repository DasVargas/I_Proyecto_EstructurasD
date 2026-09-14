#include "ColaPiezas.h"
#include <iostream>
#include <cstdlib>
using namespace std;


// Constructor
ColaPiezas::ColaPiezas() {
	frente = nullptr;
	final = nullptr;
}
// Destructor
ColaPiezas::~ColaPiezas() {
	while (frente != nullptr) {
		NodoPieza* borrar = frente;
		frente = frente->siguiente;
		delete borrar;
	}
	final = nullptr;
}

// Insertar una pieza en la cola
void ColaPiezas::insertar(char tipo) {
	NodoPieza* nuevo = new NodoPieza;
	nuevo->tipo = tipo;
	nuevo->siguiente = nullptr;
	if (frente == nullptr) {
		frente = nuevo;
		final = nuevo;
	}
	else {
		final->siguiente = nuevo;
		final = nuevo;
	}
}
// Saber si la cola esta vacia
bool ColaPiezas::estaVacia() {
	return frente == nullptr;
}


// Sacar la primera pieza
char ColaPiezas::sacar() {
	if (frente == nullptr) {
		return ' ';
	}
	NodoPieza* borrar = frente;
	char tipo = frente->tipo;
	frente = frente->siguiente;
	delete borrar;
	if (frente == nullptr) {
		final = nullptr;
	}	
	return tipo;
}


// Mostrar la cola
void ColaPiezas::mostrar() {
	NodoPieza* actual = frente;
	while (actual != nullptr) {
		cout << actual->tipo << " ";
		actual = actual->siguiente;
	}
	cout << endl;
}

void ColaPiezas::generarBolsa() {
	char piezas[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
	for (int i = 6; i > 0; i--) {
		int posicion = rand() % (i + 1);
		char auxiliar = piezas[i];
		piezas[i] = piezas[posicion];
		piezas[posicion] = auxiliar;
	}
	for (int i = 0; i < 7; i++) {
		insertar(piezas[i]);
	}
}

void ColaPiezas::mostrarProximas3() {
	NodoPieza* actual = frente;
	int contador = 0;
	while (actual != nullptr && contador < 3) {
		cout << actual->tipo << " ";
		actual = actual->siguiente;
		contador++;
	}
	cout << endl;
}
int ColaPiezas::contar() {
	int contador = 0;
	NodoPieza* actual = frente;
	while (actual != nullptr) {
		contador++;
		actual = actual->siguiente;
	}
	return contador;
}

void ColaPiezas::mantenerCola() {
	if (contar() < 4) {
		generarBolsa();
	}
}
char ColaPiezas::obtenerPieza(int posicion) {
	NodoPieza* actual = frente;
	int contador = 0;
	
	while (actual != nullptr) {
		if (contador == posicion) {
			return actual->tipo;
		}
		actual = actual->siguiente;
		contador++;
	}
	return ' ';
}
