#include "PilaHold.h"

PilaHold::PilaHold() {
	tope = nullptr;
}

PilaHold::~PilaHold() {
	if (tope != nullptr) {
		delete tope;
		tope = nullptr;
	}
}

bool PilaHold::estaVacia() {
	return tope == nullptr;
}

void PilaHold::guardar(char tipo) {
	if (tope == nullptr) {
		tope = new NodoHold;
		tope->tipo = tipo;
		tope->siguiente = nullptr;
	}
}

char PilaHold::sacar() {
	if (tope == nullptr) {
		return ' ';
	}
	
	char tipo = tope->tipo;
	
	delete tope;
	tope = nullptr;
	
	return tipo;
}

char PilaHold::verTipo() {
	if (tope == nullptr) {
		return ' ';
	}
	return tope->tipo;
}
