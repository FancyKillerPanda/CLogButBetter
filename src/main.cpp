#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window { sf::VideoMode { 960, 540 }, "CLogButBetter" };
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
			} break;

			default:
			{
			} break;
			}

			window.clear(sf::Color { 255, 0, 0, 255 });
			window.display();
		}
	}
}
