#include <SFML/Graphics.hpp>

int main() {
	
	sf::RenderWindow ventana(
							 sf::VideoMode(800, 600),
							 "Tetris"
							 );
	
	while (ventana.isOpen()) {
		
		sf::Event evento;
		
		while (ventana.pollEvent(evento)) {
			
			if (evento.type == sf::Event::Closed) {
				ventana.close();
			}
		}
		
		ventana.clear();
		ventana.display();
	}
	
	return 0;
}
