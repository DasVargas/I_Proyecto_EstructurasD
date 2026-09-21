#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Juego.h"
#include "Puntaje.h"

using namespace std;
int main() {
	
	srand(time(NULL));
	
	bool programaAbierto = true;
	
	while (programaAbierto) {
		
		sf::RenderWindow ventana(sf::VideoMode(800, 600), "Tetris");
		
		sf::Texture texturaMenu;
		sf::Texture texturaAyuda;
		sf::Texture texturaTop10;
		
		if (!texturaMenu.loadFromFile("assets/images/menu.png")) {
			cout << "Error al cargar el menu" << endl;
			return 1;
		}
		
		if (!texturaAyuda.loadFromFile("assets/images/ayuda.png")) {
			cout << "Error al cargar la ayuda" << endl;
			return 1;
		}
		
		if (!texturaTop10.loadFromFile("assets/images/top10.png")) {
			cout << "Error al cargar Top 10" << endl;
			return 1;
		}
		
		sf::Font fuente;
		
		if (!fuente.loadFromFile("assets/fonts/Roboto.ttf")) {
			cout << "Error al cargar la fuente" << endl;
			return 1;
		}
		
		sf::Sprite fondo;
		fondo.setTexture(texturaMenu);
		
		bool ayuda = false;
		bool top10 = false;
		bool jugar = false;
		
		RegistroPuntaje puntajes[10];
		int cantidadTop = 0;
		
		while (ventana.isOpen()) {
			
			sf::Event evento;
			
			while (ventana.pollEvent(evento)) {
				
				if (evento.type == sf::Event::Closed) {
					programaAbierto = false;
					ventana.close();
				}
				
				if (evento.type == sf::Event::MouseButtonPressed &&
					evento.mouseButton.button == sf::Mouse::Left) {
					
					int x = evento.mouseButton.x;
					int y = evento.mouseButton.y;
					
					// MENU PRINCIPAL
					if (!ayuda && !top10) {
						
						// JUGAR
						if (x >= 279 && x <= 524 && y >= 238 && y <= 299) {
							jugar = true;
							ventana.close();
						}
						
						// AYUDA
						if (x >= 277 && x <= 521 && y >= 327 && y <= 382) {
							ayuda = true;
							fondo.setTexture(texturaAyuda);
						}
						
						// TOP 10
						if (x >= 276 && x <= 523 && y >= 413 && y <= 466) {
							top10 = true;
							cantidadTop = obtenerTop10(puntajes);
							fondo.setTexture(texturaTop10);
						}
					}
					
					// PANTALLA DE AYUDA
					else if (ayuda) {
						// VOLVER
						if (x >= 275 && x <= 525 && y >= 515 && y <= 580) {
							ayuda = false;
							fondo.setTexture(texturaMenu);
						}
					}
					
					// PANTALLA TOP 10
					else if (top10) {
						// VOLVER
						if (x >= 275 && x <= 525 && y >= 515 && y <= 580) {
							top10 = false;
							fondo.setTexture(texturaMenu);
						}
					}
				}
			}
			
			ventana.clear();
			ventana.draw(fondo);
			
			// MOSTRAR LOS PUNTAJES 
			if (top10) {
				for (int i = 0; i < cantidadTop; i++) {
					sf::Text nombre;
					nombre.setFont(fuente);
					nombre.setString(puntajes[i].nombre);
					nombre.setCharacterSize(16);
					nombre.setPosition(300, 174 + i * 31);
					
					sf::Text puntos;
					puntos.setFont(fuente);
					puntos.setString(to_string(puntajes[i].puntaje));
					puntos.setCharacterSize(16);
					puntos.setPosition(530, 174 + i * 31);
					
					ventana.draw(nombre);
					ventana.draw(puntos);
				}
			}
			
			ventana.display();
		}
		
		if (jugar) {
			iniciarJuego();
		}
	}
	
	return 0;
}
