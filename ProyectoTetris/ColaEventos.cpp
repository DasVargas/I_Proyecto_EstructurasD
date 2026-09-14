#include "ColaEventos.h"
#include <iostream>

using namespace std;

ColaEventos::ColaEventos() {
	frente = nullptr;
}

ColaEventos::~ColaEventos() {
	while (frente != nullptr) {
		NodoEvento* borrar = frente;
		frente = frente->siguiente;
		delete borrar;
	}
}

bool ColaEventos::estaVacia() {
	return frente == nullptr;
}

void ColaEventos::insertar(string tipo, int prioridad) {
	NodoEvento* nuevo = new NodoEvento;
	
	nuevo->tipo = tipo;
	nuevo->prioridad = prioridad;
	nuevo->siguiente = nullptr;
	
	if (frente == nullptr || prioridad < frente->prioridad) {
		nuevo->siguiente = frente;
		frente = nuevo;
		return;
	}
	
	NodoEvento* actual = frente;
	
	while (actual->siguiente != nullptr && actual->siguiente->prioridad <= prioridad) {
		actual = actual->siguiente;
	}
	
	nuevo->siguiente = actual->siguiente;
	actual->siguiente = nuevo;
}

void ColaEventos::mostrar() {
	NodoEvento* actual = frente;
	
	while (actual != nullptr) {
	cout << "Evento: " << actual->tipo << " | Prioridad: " << actual->prioridad << endl;
	actual = actual->siguiente;
	}
}
