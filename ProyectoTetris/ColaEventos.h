#ifndef COLAEVENTOS_H
#define COLAEVENTOS_H

#include <string>

using namespace std;

struct NodoEvento {
	string tipo;
	int lineas;
	NodoEvento* siguiente;
};

class ColaEventos {
private:
	NodoEvento* frente;
	
public:
	ColaEventos();
	~ColaEventos();
	
	bool estaVacia();
	void insertar(string tipo, int lineas);
	bool eventoListo(int totalLineas);
	string sacar();
	void mostrar();
};

#endif
