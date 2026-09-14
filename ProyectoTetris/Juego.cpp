#include "Juego.h"
#include "Movimiento.h"
#include "Puntaje.h"
#include "PilaHold.h"
#include "Historial.h"
#include "ColaEventos.h"
#include <string>
#include <iostream>
using namespace std;

void dibujarTablero(sf::RenderWindow& ventana, Tablero& tablero) {
	for (int fila = 0; fila < FILAS; fila++) {
		for (int columna = 0; columna < COLUMNAS; columna++) {
			sf::RectangleShape celda(sf::Vector2f(30, 30));
			celda.setPosition(300 + columna * 30, 50 + fila * 30);
			
			int valor = tablero.getCelda(fila, columna);
			
			if (valor != 0) {
				celda.setFillColor(obtenerColor(valor));
			}
			else {
				celda.setFillColor(sf::Color::Black);
			}
			
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
				300 + (pieza.getColumna() + columna) * 30,
				50 + (pieza.getFila() + fila) * 30);
				
				celda.setFillColor(obtenerColor(pieza.getValor()));
				celda.setOutlineColor(sf::Color::White);
				celda.setOutlineThickness(1);
				
				ventana.draw(celda);
			}
		}
	}
}


bool colocarYSiguiente(Pieza& pieza, Tablero& tablero, ColaPiezas& cola, int& puntaje, bool& usoHold, int& lineasEliminadas) {
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
	sf::RenderWindow ventana(sf::VideoMode(900, 750), "Tetris");
	sf::Font fuente;
	
	if (!fuente.loadFromFile("assets/fonts/Roboto.ttf")) {
		cout << "Error al cargar la fuente" << endl;
	}
	
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
	int totalLineas = 0;
	
	bool usoHold = false;
	bool enReplay = false;
	bool replayTerminado = false;
	bool pausado = false;
	
	while (ventana.isOpen()) {
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				ventana.close();
			}
			if (evento.type == sf::Event::KeyPressed &&
				evento.key.code == sf::Keyboard::P && !gameOver) {
				
				pausado = !pausado;
				
				relojCaida.restart();
			}
			if (evento.type == sf::Event::KeyPressed && !gameOver && !pausado) {
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
						bool continua = colocarYSiguiente(pieza, tablero, cola, puntaje, usoHold, lineasEliminadas);
						
						totalLineas += lineasEliminadas;
						
						if (!continua) {
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
		
		if (!gameOver && !pausado &&relojCaida.getElapsedTime().asSeconds() >= tiempoCaida) {
			if (moverAbajo(pieza, tablero)) {
				registrarMovimiento(historial, 'B', pieza, tablero);
			}
			else {
				bool continua = colocarYSiguiente(pieza, tablero, cola, puntaje, usoHold, lineasEliminadas);
				
				totalLineas += lineasEliminadas;
				
				if (!continua) {
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
		
		escribirTexto(ventana, fuente, "HOLD", 120, 35, 22);
		escribirTexto(ventana, fuente, "NEXT", 720, 35, 22);
		
		escribirTexto(ventana, fuente, "SCORE\n" + std::to_string(puntaje), 110, 350, 22);
		escribirTexto(ventana, fuente, "LINES\n" + std::to_string(totalLineas), 110, 450, 22);
		
		if (pausado) {
			dibujarPieza(ventana, pieza);
			ventana.setTitle("Tetris - PAUSA");
		}
		else if (!gameOver) {
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
	cuadro.setPosition(70, 70);
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
				105 + columna * 25,
				100 + fila * 25);
				
				celda.setFillColor(obtenerColor(piezaHold.getValor()));
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
	cuadro.setPosition(660, 70);
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
						celda.setPosition(705 + columna * 20, 100 + p * 100 + fila * 20);
						celda.setFillColor(obtenerColor(siguiente.getValor()));
						celda.setOutlineColor(sf::Color::White);
						celda.setOutlineThickness(1);
						
						ventana.draw(celda);
					}
				}
			}
		}
	}
}

sf::Color obtenerColor(int valor) {
	if (valor == 1)
		return sf::Color::Cyan;
	
	if (valor == 2)
		return sf::Color::Yellow;
	
	if (valor == 3)
		return sf::Color(160, 32, 240);
	
	if (valor == 4)
		return sf::Color::Green;
	
	if (valor == 5)
		return sf::Color::Red;
	
	if (valor == 6)
		return sf::Color::Blue;
	
	if (valor == 7)
		return sf::Color(255, 165, 0);
	
	return sf::Color::Black;
}

void escribirTexto(sf::RenderWindow& ventana, sf::Font& fuente, string texto, int x, int y, int tamano) {
	sf::Text mensaje;
	
	mensaje.setFont(fuente);
	mensaje.setString(texto);
	mensaje.setCharacterSize(tamano);
	mensaje.setFillColor(sf::Color::White);
	mensaje.setPosition(x, y);
	
	ventana.draw(mensaje);
}
