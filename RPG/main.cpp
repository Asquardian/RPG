#include <SFML/Graphics.hpp>
#include "Playable.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "RPG"); //окно 800 на 600
	Playable character;
	character.SaveStatus();
	window.setVerticalSyncEnabled(true); // ставим вертикальную синхронизацию
	while (window.isOpen()) {

		sf::Event event; // на случай, если мы хотим, чтобы окно закрывалось 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



	}
	return 0;
}