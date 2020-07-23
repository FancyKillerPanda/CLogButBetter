//  ===== Date Created: 23 July, 2020 ===== 

#if !defined(TEXTBOX_HPP)
#define TEXTBOX_HPP

#include <string>
#include <SFML/Graphics.hpp>

class TextBox
{
private:
	bool isActive = false;

	std::string displayedText;
	std::string textValue;

	sf::Text drawableText;
	sf::RectangleShape backgroundShape;
	sf::Vector2i centrePosition;
	sf::Vector2i size;

public:
	TextBox(const sf::Font& font, sf::Vector2i centrePosition, sf::Vector2i size);

	void handleMouseUp(sf::Vector2i& mousePos);
	void handleTextInput(sf::Event& event);
	void draw(sf::RenderTarget& target);

	void setActive(bool value);
};

#endif
