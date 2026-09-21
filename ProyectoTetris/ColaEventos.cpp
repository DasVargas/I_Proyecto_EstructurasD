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

void ColaEventos::insertar(string tipo, int lineas) {
	NodoEvento* nuevo = new NodoEvento;
	
	nuevo->tipo = tipo;
	nuevo->lineas = lineas;
	nuevo->siguiente = nullptr;
	
	if (frente == nullptr || lineas < frente->lineas) {
		nuevo->siguiente = frente;
		frente = nuevo;
		return;
	}
	
	NodoEvento* actual = frente;
	
	while (actual->siguiente != nullptr && actual->siguiente->lineas <= lineas) {
		actual = actual->siguiente;
	}
	
	nuevo->siguiente = actual->siguiente;
	actual->siguiente = nuevo;
}

bool ColaEventos::eventoListo(int totalLineas) {
	if (frente == nullptr) {
		return false;
	}
	
	return totalLineas >= frente->lineas;
}

string ColaEventos::sacar() {
	if (frente == nullptr) {
		return "";
	}
	
	NodoEvento* borrar = frente;
	string tipo = borrar->tipo;
	
	frente = frente->siguiente;
	
	delete borrar;
	
	return tipo;
}

void ColaEventos::mostrar() {
	NodoEvento* actual = frente;
	
	while (actual != nullptr) {
		cout << "Evento: " << actual->tipo << " | Lineas: " << actual->lineas << endl;
		actual = actual->siguiente;
	}
}
