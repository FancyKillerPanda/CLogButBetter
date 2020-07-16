// ===== Date Created: 15 July, 2020 =====

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "button.hpp"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#define HOME_PATH_BUTTON_WIDTH WINDOW_WIDTH * 20 / 100
#define HOME_PATH_BUTTON_HEIGHT WINDOW_HEIGHT * 10 / 100

// Will be used to access buttons in the vector. Rather than using a
// plain index, these names help to understand which button is being
// accessed.
enum ButtonIndex
{
	VIEW_CADETS_BUTTON,
	VIEW_SQUADRON_BUTTON,
	ISSUES_BUTTON,
	EXCHANGES_BUTTON,
	RETURNS_BUTTON,
	MANAGE_BUTTON,

	// Keep last
	BUTTON_COUNT,
};

std::vector<Button> initAllButtons(const sf::Font& font)
{
	// NOTE(fkp): Volatile, initilise in order of ButtonIndex
	std::vector<Button> result;
	result.reserve(BUTTON_COUNT);
	sf::Vector2i buttonSize { HOME_PATH_BUTTON_WIDTH, HOME_PATH_BUTTON_HEIGHT };

	result.emplace_back(font, "View Cadets",
						sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 40 / 100 },
						buttonSize);
	result.emplace_back(font, "View Squadron",
						sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 60 / 100 },
						buttonSize);
	result.emplace_back(font, "Issues",
						sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 30 / 100 },
						buttonSize);
	result.emplace_back(font, "Exchanges",
						sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 50 / 100 },
						buttonSize);
	result.emplace_back(font, "Returns",
						sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 70 / 100 },
						buttonSize);
	result.emplace_back(font, "Manage",
						sf::Vector2i { WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 50 / 100 },
						buttonSize);

	return result;
}

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

	std::vector<Button> buttons = initAllButtons(font);

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

			case sf::Event::MouseMoved:
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				for (Button& button : buttons)
				{
					button.handleMouseMove(mousePos);
				}
			} break;

			case sf::Event::MouseButtonPressed:
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				
				for (Button& button : buttons)
				{
					button.handleMouseDown(mousePos);
				}
			} break;

			case sf::Event::MouseButtonReleased:
			{
				for (Button& button : buttons)
				{
					if (button.handleMouseUp())
					{
						printf("Button clicked.\n");
					}
				}
			} break;

			default:
			{
			} break;
			}
		}
		
		window.clear(sf::Color { 153, 216, 233, 255 });
		window.draw(titleText);

		for (Button& button : buttons)
		{
			button.draw(window);
		}
		
		window.display();
	}
}
