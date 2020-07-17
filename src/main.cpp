// ===== Date Created: 15 July, 2020 =====

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "clogbutbetter.hpp"

int main()
{
	sf::RenderWindow window { sf::VideoMode { WINDOW_WIDTH, WINDOW_HEIGHT }, "CLogButBetter" };
	sf::Event event;

	CLogButBetter clogButBetter {};
	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			clogButBetter.handleProgramEvent(window, event);
		}
		
		window.clear(sf::Color { 153, 216, 233, 255 });
		clogButBetter.drawProgram(window);
		window.display();
	}
}
