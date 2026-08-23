#ifndef TABLERO_H
#define TABLERO_H

const int FILAS = 20;
const int COLUMNAS = 10;

struct NodoFila {
	int celdas[COLUMNAS];
	NodoFila* siguiente;
};

class Tablero {
private:
	NodoFila* cabeza;
	
public:
	Tablero();
	~Tablero();
	
	void crearTablero();
	void mostrarTablero();
};

#endif
