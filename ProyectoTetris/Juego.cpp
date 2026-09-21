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
			sf::RectangleShape celda(sf::Vector2f(23, 23));
			celda.setPosition(272 + columna * 23, 55 + fila * 23);
			
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
				
				sf::RectangleShape celda(sf::Vector2f(23, 23));
				
				celda.setPosition(
				272 + (pieza.getColumna() + columna) * 23,
				55 + (pieza.getFila() + fila) * 23);
				
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
	sf::RenderWindow ventana(sf::VideoMode(800,600), "Tetris");
	
	sf::View vista(sf::FloatRect(0, 0, 800, 600));
	ajustarVista(ventana, vista);
	
	sf::Font fuente;
	sf::Texture texturaFondo;
	
	if (!fuente.loadFromFile("assets/fonts/Roboto.ttf")) {
		cout << "Error al cargar la fuente" << endl;
	}
	
	if (!texturaFondo.loadFromFile("assets/images/fondo.png")) {
		cout << "Error al cargar el fondo" << endl;
	}
	
	sf::Sprite fondo;
	fondo.setTexture(texturaFondo);
	fondo.setPosition(0, 0);
	
	Tablero tablero;
	
	ColaPiezas cola;
	cola.generarBolsa();
	
	PilaHold hold;
	Historial historial;
	ColaEventos eventos;
	eventos.insertar("BONUS PUNTOS", 15);
	eventos.insertar("ACTIVAR FANTASMA", 5);
	eventos.insertar("AUMENTAR VELOCIDAD", 10);
	
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
	bool fantasmaActiva = false;
	
	while (ventana.isOpen()) {
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				ventana.close();
			}
			if (evento.type == sf::Event::Resized) {
				ajustarVista(ventana, vista);
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
							ventana.setTitle("Tetris - GAME OVER");
						}
						else {
							if (lineasEliminadas > 0) {
								eventos.insertar("LINEA ELIMINADA", 2);
							}
							else{
							registrarMovimiento(historial, 'P', pieza, tablero);
							}
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
		while (eventos.eventoListo(totalLineas)) {
			string eventoActual = eventos.sacar();
			
			if (eventoActual == "ACTIVAR FANTASMA") {
				fantasmaActiva = true;
			}
			
			if (eventoActual == "AUMENTAR VELOCIDAD") {
				tiempoCaida = 0.7f;
			}
			
			if (eventoActual == "BONUS PUNTOS") {
				puntaje += 500;
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
					ventana.setTitle("Tetris - GAME OVER");
				}
				else {
					if (lineasEliminadas > 0) {
						eventos.insertar("LINEA ELIMINADA", 2);
					}
					else{
					registrarMovimiento(historial, 'P', pieza, tablero);
					}
					
				}
			}
			
			relojCaida.restart();
		}
		
		ventana.clear(sf::Color::Black);
		ventana.setView(vista);
		ventana.draw(fondo);
		
		dibujarTablero(ventana, tablero);
		dibujarHold(ventana, hold);
		dibujarProximas3(ventana, cola);
		
		escribirTexto(ventana, fuente, std::to_string(puntaje), 125, 305, 24);
		escribirTexto(ventana, fuente, std::to_string(totalLineas), 125, 395, 24);
		
		if (pausado) {
			dibujarPieza(ventana, pieza);
			ventana.setTitle("Tetris - PAUSA");
		}
		else if (!gameOver) {
			if (fantasmaActiva) {
				dibujarFantasma(ventana, pieza, tablero);
				
			}
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
	if (hold.estaVacia()) {
		return;
	}
	
	Pieza piezaHold(hold.verTipo());
	dibujarPiezaPequena(ventana, piezaHold, 145, 165, 20);
}

void registrarMovimiento(Historial& historial, char movimiento, Pieza& pieza, Tablero& tablero) {
	historial.agregar(movimiento, pieza, tablero);
}

void dibujarProximas3(sf::RenderWindow& ventana, ColaPiezas& cola) {
	for (int p = 0; p < 3; p++) {
		char tipo = cola.obtenerPieza(p);
		
		if (tipo != ' ') {
			Pieza siguiente(tipo);
			dibujarPiezaPequena(ventana, siguiente, 635, 145 + p * 80, 18);
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

void dibujarPiezaPequena(sf::RenderWindow& ventana, Pieza& pieza, int centroX, int centroY, int tamano) {
	int minFila = 4;
	int maxFila = -1;
	int minColumna = 4;
	int maxColumna = -1;
	
	for (int fila = 0; fila < 4; fila++) {
		for (int columna = 0; columna < 4; columna++) {
			if (pieza.getCelda(fila, columna) == 1) {
				if (fila < minFila) minFila = fila;
				if (fila > maxFila) maxFila = fila;
				if (columna < minColumna) minColumna = columna;
				if (columna > maxColumna) maxColumna = columna;
			}
		}
	}
	
	int ancho = (maxColumna - minColumna + 1) * tamano;
	int alto = (maxFila - minFila + 1) * tamano;
	
	int inicioX = centroX - ancho / 2;
	int inicioY = centroY - alto / 2;
	
	for (int fila = minFila; fila <= maxFila; fila++) {
		for (int columna = minColumna; columna <= maxColumna; columna++) {
			if (pieza.getCelda(fila, columna) == 1) {
				sf::RectangleShape celda(sf::Vector2f(tamano, tamano));
				celda.setPosition(inicioX + (columna - minColumna) * tamano, inicioY + (fila - minFila) * tamano);
				celda.setFillColor(obtenerColor(pieza.getValor()));
				celda.setOutlineColor(sf::Color::White);
				celda.setOutlineThickness(1);
				ventana.draw(celda);
			}
		}
	}
}
void ajustarVista(sf::RenderWindow& ventana, sf::View& vista) {
	float proporcionVentana = ventana.getSize().x / (float)ventana.getSize().y;
	float proporcionJuego = 800.0f / 600.0f;
	
	float ancho = 1.0f;
	float alto = 1.0f;
	float x = 0.0f;
	float y = 0.0f;
	
	if (proporcionVentana > proporcionJuego) {
		ancho = proporcionJuego / proporcionVentana;
		x = (1.0f - ancho) / 2.0f;
	}
	else {
		alto = proporcionVentana / proporcionJuego;
		y = (1.0f - alto) / 2.0f;
	}
	
	vista.setViewport(sf::FloatRect(x, y, ancho, alto));
	ventana.setView(vista);
}
void dibujarFantasma(sf::RenderWindow& ventana, Pieza& pieza, Tablero& tablero) {
	Pieza fantasma = pieza;
	
	while (puedeMover(fantasma, tablero, fantasma.getFila() + 1, fantasma.getColumna())) {
		fantasma.setFila(fantasma.getFila() + 1);
	}
	
	for (int fila = 0; fila < 4; fila++) {
		for (int columna = 0; columna < 4; columna++) {
			if (fantasma.getCelda(fila, columna) == 1) {
				sf::RectangleShape celda(sf::Vector2f(23, 23));
				
				celda.setPosition(272 + (fantasma.getColumna() + columna) * 23, 55 + (fantasma.getFila() + fila) * 23);
				
				sf::Color color = obtenerColor(fantasma.getValor());
				color.a = 70;
				
				celda.setFillColor(color);
				celda.setOutlineColor(obtenerColor(fantasma.getValor()));
				celda.setOutlineThickness(1);
				
				ventana.draw(celda);
			}
		}
	}
}
