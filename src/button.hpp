//  ===== Date Created: 15 July, 2020 ===== 

#if !defined(BUTTON_HPP)
#define BUTTON_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Button
{
private:
	std::string text;
	sf::Text drawableText;
	sf::Vector2i centrePosition;
	sf::Vector2i size;
	
public:
	Button(const sf::Font& font, std::string text, sf::Vector2i centrePosition, sf::Vector2i size);
	void draw(sf::RenderTarget& target);
};

#endif
