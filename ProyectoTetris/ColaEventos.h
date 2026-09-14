#ifndef COLAEVENTOS_H
#define COLAEVENTOS_H
#include <string>

using namespace std;

struct NodoEvento {
	string tipo;
	int prioridad;
	NodoEvento* siguiente;
};

class ColaEventos {
private:
	NodoEvento* frente;
	
public:
	ColaEventos();
	~ColaEventos();
	
	bool estaVacia();
	void insertar(string tipo, int prioridad);
	void mostrar();
};

#endif
