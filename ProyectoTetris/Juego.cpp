#include "Juego.h"
#include "Movimiento.h"
#include "Puntaje.h"
#include "PilaHold.h"
#include "Historial.h"
#include "ColaEventos.h"
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
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
void dibujarGameOver(sf::RenderWindow& ventana, sf::Font& fuente,int puntaje, string nombreJugador, bool puntajeGuardado) {
	// Oscurece el juego que queda detras
	sf::RectangleShape oscuro(sf::Vector2f(800, 600));
	oscuro.setFillColor(sf::Color(0, 0, 0, 180));
	ventana.draw(oscuro);
	
	// Cuadro principal
	sf::RectangleShape cuadro(sf::Vector2f(420, 350));
	cuadro.setPosition(190, 125);
	cuadro.setFillColor(sf::Color(15, 15, 35));
	cuadro.setOutlineThickness(4);
	cuadro.setOutlineColor(sf::Color::Cyan);
	ventana.draw(cuadro);
	
	if (!puntajeGuardado) {
		escribirTexto(ventana, fuente, "GAME OVER", 310, 150, 32);
		
		escribirTexto(ventana, fuente, "PUNTAJE FINAL", 315, 205, 20);
		escribirTexto(ventana, fuente, to_string(puntaje), 380, 235, 24);
		
		escribirTexto(ventana, fuente, "NOMBRE", 350, 285, 18);
		escribirTexto(ventana, fuente, nombreJugador, 300, 315, 22);
		
		escribirTexto(ventana, fuente, "ENTER - GUARDAR PUNTAJE", 270, 385, 18);
	}
	else {
		escribirTexto(ventana, fuente, "PUNTAJE GUARDADO", 285, 190, 26);
		
		escribirTexto(ventana, fuente, "PUNTAJE FINAL", 315, 245, 20);
		escribirTexto(ventana, fuente, to_string(puntaje), 380, 275, 24);
		
		escribirTexto(ventana, fuente, "R - VER REPLAY", 325, 320, 18);
		escribirTexto(ventana, fuente, "ESPACIO - SIGUIENTE PASO", 285, 350, 16);
		
		sf::RectangleShape botonVolver(sf::Vector2f(220, 45));
		botonVolver.setPosition(290, 390);
		botonVolver.setFillColor(sf::Color(30, 30, 60));
		botonVolver.setOutlineThickness(2);
		botonVolver.setOutlineColor(sf::Color::Cyan);
		
		ventana.draw(botonVolver);
		
		escribirTexto(ventana, fuente, "VOLVER AL MENU", 320, 400, 18);
	}
}

void dibujarPausa(sf::RenderWindow& ventana, sf::Font& fuente) {
	// Oscurecer el juego
	sf::RectangleShape oscuro(sf::Vector2f(800, 600));
	oscuro.setFillColor(sf::Color(0, 0, 0, 180));
	ventana.draw(oscuro);
	
	// Cuadro de pausa
	sf::RectangleShape cuadro(sf::Vector2f(400, 200));
	cuadro.setPosition(200, 200);
	cuadro.setFillColor(sf::Color(15, 15, 35));
	cuadro.setOutlineThickness(4);
	cuadro.setOutlineColor(sf::Color::Cyan);
	ventana.draw(cuadro);
	
	escribirTexto(ventana, fuente, "JUEGO PAUSADO", 285, 245, 30);
	escribirTexto(ventana, fuente, "P - CONTINUAR JUGANDO", 275, 325, 18);
}

void iniciarJuego() {
	sf::RenderWindow ventana(sf::VideoMode(800, 600), "Tetris");
	
	sf::View vista(sf::FloatRect(0, 0, 800, 600));
	ajustarVista(ventana, vista);
	
	sf::Font fuente;
	sf::Texture texturaFondo;
	
	if (!fuente.loadFromFile("assets/fonts/PixelOperator-Bold.ttf")) {
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
	bool usoHold = false;
	bool enReplay = false;
	bool replayTerminado = false;
	bool pausado = false;
	bool fantasmaActiva = false;
	bool puntajeGuardado = false;
	
	bool wPresionada = false;
	
	int puntaje = 0;
	int lineasEliminadas = 0;
	int totalLineas = 0;
	
	string nombreJugador = "";
	
	sf::Music musica;
	
	if (!musica.openFromFile("assets/audio/musica.ogg")) {
		cout << "Error al cargar la musica" << endl;
	}
	else {
		musica.setLoop(true);
		musica.setVolume(40);
		musica.play();
	}
	while (ventana.isOpen()) {
		
		sf::Event evento;
		
		while (ventana.pollEvent(evento)) {
			
			if (evento.type == sf::Event::Closed) {
				ventana.close();
			}
			
			if (evento.type == sf::Event::Resized) {
				ajustarVista(ventana, vista);
			}
			
			// ESCRIBIR NOMBRE EN GAME OVER
			if (evento.type == sf::Event::TextEntered &&
				gameOver && !puntajeGuardado && !enReplay) {
				
				if (evento.text.unicode == 8) {
					if (!nombreJugador.empty()) {
						nombreJugador.erase(nombreJugador.size() - 1);
					}
				}
				else if (evento.text.unicode >= 32 && evento.text.unicode <= 126 && nombreJugador.size() < 12) {
					nombreJugador += static_cast<char>(evento.text.unicode);
				}
			}
			// SOLTAR W
			if (evento.type == sf::Event::KeyReleased &&
				evento.key.code == sf::Keyboard::W) {
				
				wPresionada = false;
			}
			// PAUSA
			if (evento.type == sf::Event::KeyPressed &&
				evento.key.code == sf::Keyboard::P && !gameOver) {
				
				pausado = !pausado;
				relojCaida.restart();
				
				if (pausado) {
					musica.pause();
				}
				else {
					musica.play();
				}
			}
			
			// CONTROLES NORMALES
			if (evento.type == sf::Event::KeyPressed &&
				!gameOver && !pausado) {
				
				// IZQUIERDA
				if (evento.key.code == sf::Keyboard::A) {
					int columnaAnterior = pieza.getColumna();
					moverIzquierda(pieza, tablero);
					if (pieza.getColumna() != columnaAnterior) {
						registrarMovimiento(historial, 'I', pieza, tablero);
					}
				}
				
				// DERECHA
				if (evento.key.code == sf::Keyboard::D) {
					int columnaAnterior = pieza.getColumna();
					moverDerecha(pieza, tablero);
					if (pieza.getColumna() != columnaAnterior) {
						registrarMovimiento(historial, 'D', pieza, tablero);
					}
				}
				
				// ABAJO
				if (evento.key.code == sf::Keyboard::S) {
					if (moverAbajo(pieza, tablero)) {
						registrarMovimiento(historial, 'B', pieza, tablero);
					}
					else {
						bool continua = colocarYSiguiente(pieza, tablero, cola, puntaje, usoHold, lineasEliminadas);
						totalLineas += lineasEliminadas;
						if (!continua) {
							gameOver = true;
						}
						else {
							registrarMovimiento(historial, 'P', pieza, tablero);
						}
					}
				}
				
				// ROTAR
				if (evento.key.code == sf::Keyboard::W && !wPresionada) {
					wPresionada = true;
					int orientacionAnterior = pieza.getOrientacion();
					rotarPieza(pieza, tablero);
					if (pieza.getOrientacion() != orientacionAnterior) {
						registrarMovimiento(historial, 'R', pieza, tablero);
					}
				}
				
				// HOLD
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
				
				// UNDO
				if (evento.key.code == sf::Keyboard::Z) {
					if (historial.deshacer(pieza, tablero)) {
						relojCaida.restart();
					}
				}
				
				// REDO
				if (evento.key.code == sf::Keyboard::Y) {
					if (historial.rehacer(pieza, tablero)) {
						relojCaida.restart();
					}
				}
			}
			
			// CONTROLES GAME OVER
			if (evento.type == sf::Event::KeyPressed && gameOver) {
				// GUARDAR PUNTAJE
				if (evento.key.code == sf::Keyboard::Enter &&
					!puntajeGuardado && !nombreJugador.empty()) {
					guardarPuntaje(nombreJugador, puntaje);
					puntajeGuardado = true;
				}
					// INICIAR REPLAY
					if (evento.key.code == sf::Keyboard::R && puntajeGuardado) {
						historial.iniciarReplay(pieza, tablero);
						enReplay = true;
						replayTerminado = false;
					}
					
					// AVANZAR REPLAY
					if (evento.key.code == sf::Keyboard::Space && enReplay) {
						if (!historial.avanzarReplay(pieza, tablero)) {
							enReplay = false;
							replayTerminado = true;
						}
					}
			}
			// MODAL 
			if (evento.type == sf::Event::MouseButtonPressed &&
				gameOver && puntajeGuardado && !enReplay) {
				
				if (evento.mouseButton.button == sf::Mouse::Left) {
					
					sf::Vector2i pixel(evento.mouseButton.x, evento.mouseButton.y);
					sf::Vector2f mouse = ventana.mapPixelToCoords(pixel, vista);
					
					if (mouse.x >= 290 && mouse.x <= 510 &&
						mouse.y >= 400 && mouse.y <= 445) {
						
						ventana.close();
					}
				}
			}
		}
		
		// EVENTOS ESPECIALES
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
		
		// CAIDA AUTOMATICA
		if (!gameOver && !pausado &&
			relojCaida.getElapsedTime().asSeconds() >= tiempoCaida) {

			if (moverAbajo(pieza, tablero)) {
				registrarMovimiento(historial, 'B', pieza, tablero);
			}
			else {
				bool continua = colocarYSiguiente(pieza, tablero, cola, puntaje, usoHold, lineasEliminadas);
				totalLineas += lineasEliminadas;
				if (!continua) {
					gameOver = true;
				}
				else {
					registrarMovimiento(historial, 'P', pieza, tablero);
				}
			}
			relojCaida.restart();
		}
		
		// DIBUJAR
		ventana.clear(sf::Color::Black);
		ventana.setView(vista);
		
		ventana.draw(fondo);
		
		dibujarTablero(ventana, tablero);
		dibujarHold(ventana, hold);
		dibujarProximas3(ventana, cola);
		
		escribirTexto(ventana, fuente, to_string(puntaje), 125, 305, 24);
		escribirTexto(ventana, fuente, to_string(totalLineas), 125, 395, 24);
		
		if (pausado) {
			dibujarPieza(ventana, pieza);
		}
		else if (!gameOver) {
			if (fantasmaActiva) {
				dibujarFantasma(ventana, pieza, tablero);
			}
			dibujarPieza(ventana, pieza);
		}
		else if (enReplay) {
			dibujarPieza(ventana, pieza);
		}
		else if (replayTerminado) {
			dibujarPieza(ventana, pieza);
		}
		
		// MODAL DE PAUSA
		if (pausado) {
			dibujarPausa(ventana, fuente);
		}
		// MODAL DE GAME OVER
		if (gameOver && !enReplay) {
			dibujarGameOver(ventana, fuente, puntaje, nombreJugador, puntajeGuardado);
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
