#ifndef PILAHOLD_H
#define PILAHOLD_H

struct NodoHold {
	char tipo;
	NodoHold* siguiente;
};

class PilaHold {
private:
	NodoHold* tope;
	
public:
	PilaHold();
	~PilaHold();
	
	bool estaVacia();
	void guardar(char tipo);
	char sacar();
	char verTipo();
};

#endif
