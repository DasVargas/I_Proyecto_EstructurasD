#include "Juego.h"
#include "Movimiento.h"
#include "Puntaje.h"
#include "PilaHold.h"
#include <string>

void dibujarTablero(sf::RenderWindow& ventana, Tablero& tablero) {
	for (int fila = 0; fila < FILAS; fila++) {
		for (int columna = 0; columna < COLUMNAS; columna++) {
			sf::RectangleShape celda(sf::Vector2f(30, 30));
			celda.setPosition(50 + columna * 30, 50 + fila * 30);
			
			if (tablero.getCelda(fila, columna) == 1)
				celda.setFillColor(sf::Color::Green);
			else
				celda.setFillColor(sf::Color::Black);
			
			celda.setOutlineColor(sf::Color::White);
			celda.setOutlineThickness(1);
			
			ventana.draw(celda);
		}
	}
}


void dibujarPieza(sf::RenderWindow& ventana, Pieza& pieza) {
	for (int fila = 0; fila < 4; fila++) {
		for (int columna = 0; columna < 4; columna++) {
			if (pieza.getCelda(fila, columna) == 1) {
				
				sf::RectangleShape celda(sf::Vector2f(30, 30));
				
				celda.setPosition(
				50 + (pieza.getColumna() + columna) * 30,
				50 + (pieza.getFila() + fila) * 30);
				
				celda.setFillColor(sf::Color::Green);
				celda.setOutlineColor(sf::Color::White);
				celda.setOutlineThickness(1);
				
				ventana.draw(celda);
			}
		}
	}
}


bool colocarYSiguiente(Pieza& pieza, Tablero& tablero, ColaPiezas& cola, int& puntaje, bool& usoHold) {
	colocarPieza(pieza, tablero);
	int lineas = tablero.limpiarFilas();
	puntaje += calcularPuntos(lineas);
	cola.mantenerCola();
	char tipo = cola.sacar();
	pieza = Pieza(tipo);
	usoHold = false;
	if (!puedeMover(pieza, tablero, pieza.getFila(), pieza.getColumna())) {
		return false;
	}
	return true;
}


void iniciarJuego() {
	sf::RenderWindow ventana(sf::VideoMode(600, 800), "Tetris");
	Tablero tablero;
	
	ColaPiezas cola;
	cola.generarBolsa();
	
	PilaHold hold;
	
	char tipo = cola.sacar();
	Pieza pieza(tipo);
	
	sf::Clock relojCaida;
	
	float tiempoCaida = 1.0f;
	bool gameOver = false;
	int puntaje = 0;
	
	bool usoHold = false;
	
	while (ventana.isOpen()) {
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				ventana.close();
			}
			if (evento.type == sf::Event::KeyPressed && !gameOver) {
				if (evento.key.code == sf::Keyboard::A) {
					moverIzquierda(pieza, tablero);
				}
				if (evento.key.code == sf::Keyboard::D) {
					moverDerecha(pieza, tablero);
				}
				if (evento.key.code == sf::Keyboard::S) {
					if (!moverAbajo(pieza, tablero)) {
						if (!colocarYSiguiente(pieza, tablero, cola, puntaje,usoHold)) {
							gameOver = true;
							ventana.setTitle("Tetris - GAME OVER");
						}
					}
				}
				if (evento.key.code == sf::Keyboard::W) {
					rotarPieza(pieza, tablero);
				}
				if (evento.key.code == sf::Keyboard::C && !usoHold) {
					char tipoActual = pieza.getTipo();
					if (hold.estaVacia()) {
						hold.guardar(tipoActual);
						cola.mantenerCola();
						char siguiente = cola.sacar();
						pieza = Pieza(siguiente);
					}
					else {
						char tipoHold = hold.sacar();
						hold.guardar(tipoActual);
						pieza = Pieza(tipoHold);
					}
					usoHold = true;
				}
			}
		}
		
		if (!gameOver && relojCaida.getElapsedTime().asSeconds() >= tiempoCaida) {
			if (!moverAbajo(pieza, tablero)) {
				if (!colocarYSiguiente(pieza, tablero, cola, puntaje,usoHold )) {
					gameOver = true;
					ventana.setTitle("Tetris - GAME OVER");
				}
			}
			relojCaida.restart();
		}
		ventana.clear();
		
		dibujarTablero(ventana, tablero);
		dibujarHold(ventana, hold);
		
		if (!gameOver) {
			dibujarPieza(ventana, pieza);
			ventana.setTitle("Tetris - Puntaje: " + std::to_string(puntaje));
		}
		
		ventana.display();
	}
}
void dibujarHold(sf::RenderWindow& ventana, PilaHold& hold) {
	sf::RectangleShape cuadro(sf::Vector2f(170, 150));
	cuadro.setPosition(390, 50);
	cuadro.setFillColor(sf::Color::Black);
	cuadro.setOutlineColor(sf::Color::White);
	cuadro.setOutlineThickness(2);
	
	ventana.draw(cuadro);
	
	if (hold.estaVacia()) {
		return;
	}
	
	Pieza piezaHold(hold.verTipo());
	
	for (int fila = 0; fila < 4; fila++) {
		for (int columna = 0; columna < 4; columna++) {
			if (piezaHold.getCelda(fila, columna) == 1) {
				sf::RectangleShape celda(sf::Vector2f(25, 25));
				
				celda.setPosition(
				420 + columna * 25,
				75 + fila * 25
				);
				
				celda.setFillColor(sf::Color::Green);
				celda.setOutlineColor(sf::Color::White);
				celda.setOutlineThickness(1);
				
				ventana.draw(celda);
			}
		}
	}
}
