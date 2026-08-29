#include <iostream>
#include "Pieza.h"

using namespace std;

int main() {
	
	Pieza pieza('T');
	
	cout << "Fila inicial: " << pieza.getFila() << endl;
	cout << "Columna inicial: " << pieza.getColumna() << endl;
	cout << "Orientacion inicial: " << pieza.getOrientacion() << endl;
	
	cout << endl;
	
	pieza.setFila(5);
	pieza.setColumna(4);
	
	cout << "Nueva fila: " << pieza.getFila() << endl;
	cout << "Nueva columna: " << pieza.getColumna() << endl;
	
	cout << endl;
	
	cout << "Celda [0][1]: " << pieza.getCelda(0, 1) << endl;
	cout << "Celda [0][0]: " << pieza.getCelda(0, 0) << endl;
	
	cout << endl;
	
	pieza.rotar();
	
	cout << "Orientacion despues de rotar: "
		<< pieza.getOrientacion() << endl;
	
	cout << endl;
	
	pieza.mostrarPieza();
	
	return 0;
}
