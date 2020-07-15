// ===== Date Created: 15 July, 2020 =====

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "button.hpp"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#define HOME_PATH_BUTTON_WIDTH WINDOW_WIDTH * 20 / 100
#define HOME_PATH_BUTTON_HEIGHT WINDOW_HEIGHT * 10 / 100

int main()
{
	sf::RenderWindow window { sf::VideoMode { WINDOW_WIDTH, WINDOW_HEIGHT }, "CLogButBetter" };
	sf::Event event;

	sf::Font font;
	font.loadFromFile("res/arial.ttf");

	sf::Text titleText { "415 Squadron Logistics System", font, 32 };
	SET_ORIGIN_CENTER(titleText);
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	titleText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 12 / 100);

	Button viewCadetsButton { font, "View Cadets",
							  sf::Vector2i { WINDOW_WIDTH * 30 / 100, WINDOW_HEIGHT * 40 / 100 },
							  sf::Vector2i { HOME_PATH_BUTTON_WIDTH, HOME_PATH_BUTTON_HEIGHT } };
	
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
		}
		
		window.clear(sf::Color { 153, 216, 233, 255 });

		window.draw(titleText);
		viewCadetsButton.draw(window);
		
		window.display();
	}
}
