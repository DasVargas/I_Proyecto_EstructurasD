#include "Juego.h"
#include "Movimiento.h"
#include "Puntaje.h"
#include "PilaHold.h"
#include "Historial.h"
#include "ColaEventos.h"
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


bool colocarYSiguiente(Pieza& pieza, Tablero& tablero, ColaPiezas& cola,
					   int& puntaje, bool& usoHold, int& lineasEliminadas) {
	colocarPieza(pieza, tablero);
	lineasEliminadas = tablero.limpiarFilas();
	puntaje += calcularPuntos(lineasEliminadas);
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
	Historial historial;
	ColaEventos eventos;
	
	char tipo = cola.sacar();
	Pieza pieza(tipo);
	
	historial.agregar('0', pieza, tablero);
	
	sf::Clock relojCaida;
	
	float tiempoCaida = 1.0f;
	bool gameOver = false;
	int puntaje = 0;
	int lineasEliminadas = 0;
	
	bool usoHold = false;
	bool enReplay = false;
	bool replayTerminado = false;
	
	while (ventana.isOpen()) {
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				ventana.close();
			}
			if (evento.type == sf::Event::KeyPressed && !gameOver) {
				if (evento.key.code == sf::Keyboard::A) {
					int columnaAnterior = pieza.getColumna();
					moverIzquierda(pieza, tablero);
					if (pieza.getColumna() != columnaAnterior) {
						registrarMovimiento(historial, 'I', pieza, tablero);
					}
				}
				if (evento.key.code == sf::Keyboard::D) {
					int columnaAnterior = pieza.getColumna();
					moverDerecha(pieza, tablero);
					if (pieza.getColumna() != columnaAnterior) {
						registrarMovimiento(historial, 'D', pieza, tablero);
					}
				}
				if (evento.key.code == sf::Keyboard::S) {
					if (moverAbajo(pieza, tablero)) {
						registrarMovimiento(historial, 'B', pieza, tablero);
					}
					else {
						if (!colocarYSiguiente(pieza, tablero, cola, puntaje, usoHold, lineasEliminadas)) {
							gameOver = true;
							eventos.insertar("GAME OVER", 1);
							ventana.setTitle("Tetris - GAME OVER");
						}
						else {
							eventos.insertar("PIEZA COLOCADA", 3);
							if (lineasEliminadas > 0) {
								eventos.insertar("LINEA ELIMINADA", 2);
							}
							registrarMovimiento(historial, 'P', pieza, tablero);
						}
					}
				}
				if (evento.key.code == sf::Keyboard::W) {
					int orientacionAnterior = pieza.getOrientacion();
					rotarPieza(pieza, tablero);
					if (pieza.getOrientacion() != orientacionAnterior) {
						registrarMovimiento(historial, 'R', pieza, tablero);
					}
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
				if (evento.key.code == sf::Keyboard::Z) {
					if (historial.deshacer(pieza, tablero)) {
						relojCaida.restart();
					}
				}
				if (evento.key.code == sf::Keyboard::Y) {
					if (historial.rehacer(pieza, tablero)) {
						relojCaida.restart();
					}
				}
			}
			if (evento.type == sf::Event::KeyPressed && gameOver) {
				if (evento.key.code == sf::Keyboard::R) {
					historial.iniciarReplay(pieza, tablero);
					enReplay = true;
					replayTerminado = false;
				}
				if (evento.key.code == sf::Keyboard::Space && enReplay) {
					if (!historial.avanzarReplay(pieza, tablero)) {
						enReplay = false;
						replayTerminado = true;
					}
				}
			}
		}
		
		if (!gameOver && relojCaida.getElapsedTime().asSeconds() >= tiempoCaida) {
			if (moverAbajo(pieza, tablero)) {
				registrarMovimiento(historial, 'B', pieza, tablero);
			}
			else {
				if (!colocarYSiguiente(pieza, tablero, cola, puntaje, usoHold, lineasEliminadas)) {
					gameOver = true;
					eventos.insertar("GAME OVER", 1);
					ventana.setTitle("Tetris - GAME OVER");
				}
				else {
					eventos.insertar("PIEZA COLOCADA", 3);
					if (lineasEliminadas > 0) {
						eventos.insertar("LINEA ELIMINADA", 2);
					}
					registrarMovimiento(historial, 'P', pieza, tablero);
				}
			}
			
			relojCaida.restart();
		}
		
		ventana.clear();
		
		dibujarTablero(ventana, tablero);
		dibujarHold(ventana, hold);
		dibujarProximas3(ventana, cola);
		
		if (!gameOver) {
			dibujarPieza(ventana, pieza);
			ventana.setTitle("Tetris - Puntaje: " + std::to_string(puntaje));
		}
		else if (enReplay) {
			dibujarPieza(ventana, pieza);
			ventana.setTitle("Tetris - REPLAY");
		}
		else if (replayTerminado) {
			dibujarPieza(ventana, pieza);
			ventana.setTitle("Tetris - REPLAY TERMINADO");
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
void registrarMovimiento(Historial& historial, char movimiento, Pieza& pieza, Tablero& tablero) {
	historial.agregar(movimiento, pieza, tablero);
}
void dibujarProximas3(sf::RenderWindow& ventana, ColaPiezas& cola) {
	sf::RectangleShape cuadro(sf::Vector2f(170, 350));
	cuadro.setPosition(390, 220);
	cuadro.setFillColor(sf::Color::Black);
	cuadro.setOutlineColor(sf::Color::White);
	cuadro.setOutlineThickness(2);

	ventana.draw(cuadro);	
	
	for (int p = 0; p < 3; p++) {
		char tipo = cola.obtenerPieza(p);
		
		if (tipo != ' ') {
			Pieza siguiente(tipo);
			
			for (int fila = 0; fila < 4; fila++) {
				for (int columna = 0; columna < 4; columna++) {
					if (siguiente.getCelda(fila, columna) == 1) {
						sf::RectangleShape celda(sf::Vector2f(20, 20));
						celda.setPosition(430 + columna * 20,245 + p * 100 + fila * 20);
						celda.setFillColor(sf::Color::Green);
						celda.setOutlineColor(sf::Color::White);
						celda.setOutlineThickness(1);
						
						ventana.draw(celda);
					}
				}
			}
		}
	}
}
