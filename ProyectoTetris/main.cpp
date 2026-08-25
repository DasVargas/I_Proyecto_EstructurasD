#include <iostream>
#include "Tablero.h"

using namespace std;

int main() {
	
	Tablero tablero;
	
	cout << "FILAS INICIALES: "<< tablero.contarFilas()<< endl;
	cout << endl;
	
	// Llenamos dos filas para probar
	tablero.llenarFila(18);
	tablero.llenarFila(19);
	
	cout << "ANTES DE LIMPIAR:" << endl;
	tablero.mostrarTablero();
	cout << endl;
	
	tablero.limpiarFilas();
	
	cout << "DESPUES DE LIMPIAR:" << endl;
	tablero.mostrarTablero();
	cout << endl;
	
	cout << "FILAS DESPUES DE LIMPIAR: "<< tablero.contarFilas()<< endl;
	
	return 0;
}
