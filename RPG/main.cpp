#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "RPG"); //���� 800 �� 600
	window.setVerticalSyncEnabled(true); // ������ ������������ �������������
	while (window.isOpen()) {

		sf::Event event; // �� ������, ���� �� �����, ����� ���� ����������� 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


	}
	return 0;
}