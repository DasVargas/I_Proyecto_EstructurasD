#include "Movimiento.h"

bool puedeMover(Pieza& pieza, Tablero& tablero, int nuevaFila, int nuevaColumna) {
	for (int fila = 0; fila < 4; fila++) {
		for (int columna = 0; columna < 4; columna++) {
			if (pieza.getCelda(fila, columna) == 1) {
				int filaTablero = nuevaFila + fila;
				int columnaTablero = nuevaColumna + columna;
				if (filaTablero < 0 || filaTablero >= FILAS) {
					return false;
				}
				if (columnaTablero < 0 || columnaTablero >= COLUMNAS) {
					return false;
				}
				if (tablero.getCelda(filaTablero, columnaTablero) == 1) {
					return false;
				}
			}
		}
	}
	return true;
}

void moverIzquierda(Pieza& pieza, Tablero& tablero) {
	int nuevaColumna = pieza.getColumna() - 1;
	if (puedeMover(pieza, tablero, pieza.getFila(), nuevaColumna)) {
		pieza.setColumna(nuevaColumna);
	}
}

void moverDerecha(Pieza& pieza, Tablero& tablero) {
	int nuevaColumna = pieza.getColumna() + 1;
	if (puedeMover(pieza, tablero, pieza.getFila(), nuevaColumna)) {
		pieza.setColumna(nuevaColumna);
	}
}

bool moverAbajo(Pieza& pieza, Tablero& tablero) {
	int nuevaFila = pieza.getFila() + 1;
	if (puedeMover(pieza, tablero, nuevaFila, pieza.getColumna())) {
		pieza.setFila(nuevaFila);
		return true;
	}
	return false;
}

void rotarPieza(Pieza& pieza, Tablero& tablero) {
	pieza.rotar();
	if (!puedeMover(pieza, tablero, pieza.getFila(), pieza.getColumna())) {
		pieza.rotar();
		pieza.rotar();
		pieza.rotar();
	}
}

void colocarPieza(Pieza& pieza, Tablero& tablero) {
	for (int fila = 0; fila < 4; fila++) {
		for (int columna = 0; columna < 4; columna++) {
			if (pieza.getCelda(fila, columna) == 1) {
				int filaTablero = pieza.getFila() + fila;
				int columnaTablero = pieza.getColumna() + columna;
				tablero.setCelda(filaTablero, columnaTablero, 1);
			}
		}
	}
}
