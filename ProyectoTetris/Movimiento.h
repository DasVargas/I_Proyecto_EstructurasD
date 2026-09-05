#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "Pieza.h"
#include "Tablero.h"

bool puedeMover(Pieza& pieza, Tablero& tablero, int nuevaFila, int nuevaColumna);

void moverIzquierda(Pieza& pieza, Tablero& tablero);
void moverDerecha(Pieza& pieza, Tablero& tablero);
bool moverAbajo(Pieza& pieza, Tablero& tablero);

void rotarPieza(Pieza& pieza, Tablero& tablero);
void colocarPieza(Pieza& pieza, Tablero& tablero);

#endif
