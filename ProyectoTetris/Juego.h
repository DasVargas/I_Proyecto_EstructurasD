#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "PilaHold.h"

void dibujarTablero(sf::RenderWindow& ventana, Tablero& tablero);
void dibujarPieza(sf::RenderWindow& ventana, Pieza& pieza);
bool colocarYSiguiente(Pieza& pieza, Tablero& tablero, ColaPiezas& cola, int& puntaje, bool& usoHold);
void iniciarJuego();
void dibujarHold(sf::RenderWindow& ventana, PilaHold& hold);

#endif
