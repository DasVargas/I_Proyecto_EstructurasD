#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "Tablero.h"
#include "Pieza.h"

struct NodoMovimiento {
	char movimiento;
	char tipoPieza;
	int fila;
	int columna;
	int orientacion;
	
	int estadoTablero[FILAS][COLUMNAS];
	
	NodoMovimiento* anterior;
	NodoMovimiento* siguiente;
};

class Historial {
private:
	NodoMovimiento* inicio;
	NodoMovimiento* final;
	NodoMovimiento* actual;
	NodoMovimiento* replay;
	
	void restaurarEstado(NodoMovimiento* nodo, Pieza& pieza, Tablero& tablero);
	
public:
	Historial();
	~Historial();
	
	bool estaVacio();
	
	void agregar(char movimiento, Pieza& pieza, Tablero& tablero);
	
	bool deshacer(Pieza& pieza, Tablero& tablero);
	bool rehacer(Pieza& pieza, Tablero& tablero);

	void iniciarReplay(Pieza& pieza, Tablero& tablero);
	bool avanzarReplay(Pieza& pieza, Tablero& tablero);
	
	void mostrar();
};

#endif
