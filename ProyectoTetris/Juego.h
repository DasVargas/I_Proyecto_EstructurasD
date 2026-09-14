#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "PilaHold.h"
#include "Historial.h"

void dibujarTablero(sf::RenderWindow& ventana, Tablero& tablero);
void dibujarPieza(sf::RenderWindow& ventana, Pieza& pieza);
bool colocarYSiguiente(Pieza& pieza, Tablero& tablero, ColaPiezas& cola, int& puntaje, bool& usoHold);
void iniciarJuego();
void dibujarHold(sf::RenderWindow& ventana, PilaHold& hold);
void registrarMovimiento(Historial& historial, char movimiento, Pieza& pieza, Tablero& tablero);
#endif
