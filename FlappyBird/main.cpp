#include"Game.hpp"
#include"DEFINITIONS.hpp"

int main()
{
	Engine::Game((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, "Flappy Bird");

	/*sf::RenderWindow window(sf::VideoMode(640, 480), "test");

	sf::Texture texture;
	texture.loadFromFile("Resources/images/land.png");
	sf::Sprite sprite(texture);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}*/


	return EXIT_SUCCESS;
}