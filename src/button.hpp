//  ===== Date Created: 15 July, 2020 ===== 

#if !defined(BUTTON_HPP)
#define BUTTON_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Button
{
private:
	bool isHot = false;
	bool isActive = false;
	
	std::string text;
	sf::Text drawableText;
	sf::RectangleShape backgroundShape;
	sf::Vector2i centrePosition;
	sf::Vector2i size;
	
public:
	Button(const sf::Font& font, std::string text, sf::Vector2i centrePosition, sf::Vector2i size);

	void handleMouseMove(sf::Vector2i& mousePos);
	void handleMouseDown(sf::Vector2i& mousePos);
	bool handleMouseUp();
	void draw(sf::RenderTarget& target);

	void setActive(bool value);
	void setHot(bool value);
};

#endif
