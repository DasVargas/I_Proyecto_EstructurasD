#include "Juego.h"
#include "Movimiento.h"


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


bool colocarYSiguiente(Pieza& pieza, Tablero& tablero, ColaPiezas& cola) {
	colocarPieza(pieza, tablero);
	tablero.limpiarFilas();
	cola.mantenerCola();
	char tipo = cola.sacar();
	pieza = Pieza(tipo);
	
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
	
	char tipo = cola.sacar();
	Pieza pieza(tipo);
	
	sf::Clock relojCaida;
	
	float tiempoCaida = 1.0f;
	bool gameOver = false;
	
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
						if (!colocarYSiguiente(pieza, tablero, cola)) {
							gameOver = true;
							ventana.setTitle("Tetris - GAME OVER");
						}
					}
				}
				if (evento.key.code == sf::Keyboard::W) {
					rotarPieza(pieza, tablero);
				}
			}
		}
		
		if (!gameOver && relojCaida.getElapsedTime().asSeconds() >= tiempoCaida) {
			if (!moverAbajo(pieza, tablero)) {
				if (!colocarYSiguiente(pieza, tablero, cola)) {
					gameOver = true;
					ventana.setTitle("Tetris - GAME OVER");
				}
			}
			relojCaida.restart();
		}
		ventana.clear();
		
		dibujarTablero(ventana, tablero);
		
		if (!gameOver) {
			dibujarPieza(ventana, pieza);
		}
		ventana.display();
	}
}
