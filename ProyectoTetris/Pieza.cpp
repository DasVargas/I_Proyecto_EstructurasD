#include "Pieza.h"
#include <iostream>

using namespace std;

Pieza::Pieza(char tipoPieza) {
	tipo = tipoPieza;
	orientacion = 0;
	fila = 0;
	columna = 3;
	// Inicializar todas las orientaciones en 0
	for (int o = 0; o < 4; o++) {
		for (int f = 0; f < 4; f++) {
			for (int c = 0; c < 4; c++) {
				forma[o][f][c] = 0;
			}
		}
	}
	// T 
	if (tipo == 'T') {
		// Orientacion 0
		forma[0][0][1] = 1;
		forma[0][1][0] = 1;
		forma[0][1][1] = 1;
		forma[0][1][2] = 1;
		// Orientacion 1
		forma[1][0][1] = 1;
		forma[1][1][1] = 1;
		forma[1][1][2] = 1;
		forma[1][2][1] = 1;
		// Orientacion 2
		forma[2][1][0] = 1;
		forma[2][1][1] = 1;
		forma[2][1][2] = 1;
		forma[2][2][1] = 1;
		// Orientacion 3
		forma[3][0][1] = 1;
		forma[3][1][0] = 1;
		forma[3][1][1] = 1;
		forma[3][2][1] = 1;
	}
	// I 
	if (tipo == 'I') {
		// Orientacion 0
		forma[0][1][0] = 1;
		forma[0][1][1] = 1;
		forma[0][1][2] = 1;
		forma[0][1][3] = 1;
		// Orientacion 1
		forma[1][0][2] = 1;
		forma[1][1][2] = 1;
		forma[1][2][2] = 1;
		forma[1][3][2] = 1;
		// Orientacion 2
		forma[2][2][0] = 1;
		forma[2][2][1] = 1;
		forma[2][2][2] = 1;
		forma[2][2][3] = 1;
		// Orientacion 3
		forma[3][0][1] = 1;
		forma[3][1][1] = 1;
		forma[3][2][1] = 1;
		forma[3][3][1] = 1;
	}
	// O
	if (tipo == 'O') {
		for (int o = 0; o < 4; o++) {
			forma[o][0][1] = 1;
			forma[o][0][2] = 1;
			forma[o][1][1] = 1;
			forma[o][1][2] = 1;
		}
	}
	// S 
	if (tipo == 'S') {
		// Orientacion 0
		forma[0][0][1] = 1;
		forma[0][0][2] = 1;
		forma[0][1][0] = 1;
		forma[0][1][1] = 1;
		// Orientacion 1
		forma[1][0][1] = 1;
		forma[1][1][1] = 1;
		forma[1][1][2] = 1;
		forma[1][2][2] = 1;
		// Orientacion 2
		forma[2][1][1] = 1;
		forma[2][1][2] = 1;
		forma[2][2][0] = 1;
		forma[2][2][1] = 1;
		// Orientacion 3
		forma[3][0][0] = 1;
		forma[3][1][0] = 1;
		forma[3][1][1] = 1;
		forma[3][2][1] = 1;
	}
	// Z 
	if (tipo == 'Z') {
		// Orientacion 0
		forma[0][0][0] = 1;
		forma[0][0][1] = 1;
		forma[0][1][1] = 1;
		forma[0][1][2] = 1;
		// Orientacion 1
		forma[1][0][2] = 1;
		forma[1][1][1] = 1;
		forma[1][1][2] = 1;
		forma[1][2][1] = 1;
		// Orientacion 2
		forma[2][1][0] = 1;
		forma[2][1][1] = 1;
		forma[2][2][1] = 1;
		forma[2][2][2] = 1;
		// Orientacion 3
		forma[3][0][1] = 1;
		forma[3][1][0] = 1;
		forma[3][1][1] = 1;
		forma[3][2][0] = 1;
	}
	// J 
	if (tipo == 'J') {
		// Orientacion 0
		forma[0][0][0] = 1;
		forma[0][1][0] = 1;
		forma[0][1][1] = 1;
		forma[0][1][2] = 1;
		// Orientacion 1
		forma[1][0][1] = 1;
		forma[1][0][2] = 1;
		forma[1][1][1] = 1;
		forma[1][2][1] = 1;
		// Orientacion 2
		forma[2][1][0] = 1;
		forma[2][1][1] = 1;
		forma[2][1][2] = 1;
		forma[2][2][2] = 1;
		// Orientacion 3
		forma[3][0][1] = 1;
		forma[3][1][1] = 1;
		forma[3][2][0] = 1;
		forma[3][2][1] = 1;
	}
	// L
	if (tipo == 'L') {
		// Orientacion 0
		forma[0][0][2] = 1;
		forma[0][1][0] = 1;
		forma[0][1][1] = 1;
		forma[0][1][2] = 1;
		// Orientacion 1
		forma[1][0][1] = 1;
		forma[1][1][1] = 1;
		forma[1][2][1] = 1;
		forma[1][2][2] = 1;
		// Orientacion 2
		forma[2][1][0] = 1;
		forma[2][1][1] = 1;
		forma[2][1][2] = 1;
		forma[2][2][0] = 1;
		// Orientacion 3
		forma[3][0][0] = 1;
		forma[3][0][1] = 1;
		forma[3][1][1] = 1;
		forma[3][2][1] = 1;
	}
}

int Pieza::getFila() {
	return fila;
}

int Pieza::getColumna() {
	return columna;
}

int Pieza::getOrientacion() {
	return orientacion;
}

void Pieza::setFila(int nuevaFila) {
	fila = nuevaFila;
}

void Pieza::setColumna(int nuevaColumna) {
	columna = nuevaColumna;
}

int Pieza::getCelda(int f, int c) {
	return forma[orientacion][f][c];
}

// Mostrar la orientacion actual
void Pieza::mostrarPieza() {
	for (int fila = 0; fila < 4; fila++) {
		for (int columna = 0; columna < 4; columna++) {
			cout << forma[orientacion][fila][columna] << " ";
		}
		cout << endl;
	}
}

// Cambiar de orientacion
void Pieza::rotar() {	
	orientacion++;
	if (orientacion == 4) {
		orientacion = 0;
	}
}
void Pieza::setOrientacion(int nuevaOrientacion) {
	orientacion = nuevaOrientacion;
}
