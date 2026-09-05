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
	void insertarFilaInicio();
	bool filaCompleta(NodoFila* fila);
	void eliminarFila(int posicion);
	void limpiarFilas();
	void llenarFila(int posicion);
	int contarFilas();
	
	int getCelda(int fila, int columna);
	void setCelda(int fila, int columna, int valor);
};

#endif
