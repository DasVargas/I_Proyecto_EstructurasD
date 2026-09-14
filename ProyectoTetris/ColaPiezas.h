#ifndef COLAPIEZAS_H
#define COLAPIEZAS_H

struct NodoPieza {
	char tipo;
	NodoPieza* siguiente;
};

class ColaPiezas {
private:
	
	NodoPieza* frente;
	NodoPieza* final;
	
public:
	
	ColaPiezas();
	~ColaPiezas();
	
	void insertar(char tipo);
	char sacar();
	bool estaVacia();
	void mostrar();
	
	void generarBolsa();
	void mostrarProximas3();
	int contar();
	void mantenerCola();
	char obtenerPieza(int posicion);
};

#endif
