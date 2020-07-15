//  ===== Date Created: 15 July, 2020 ===== 

#include "button.hpp"
#include "common.hpp"

Button::Button(const sf::Font& font, std::string text, sf::Vector2i centrePosition, sf::Vector2i size)
	: text(std::move(text)), centrePosition(std::move(centrePosition)), size(size)
{
	drawableText.setString(this->text);
	drawableText.setCharacterSize(24);
	drawableText.setFont(font);
	drawableText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(drawableText);
	drawableText.setPosition((sf::Vector2f) centrePosition);
}

void Button::draw(sf::RenderTarget& target)
{
	sf::RectangleShape backgroundShape { (sf::Vector2f) size };
	SET_ORIGIN_CENTER(backgroundShape);
	backgroundShape.setPosition((sf::Vector2f) centrePosition);
	backgroundShape.setFillColor(sf::Color { 216, 212, 200, 255 });

	target.draw(backgroundShape);
	target.draw(drawableText);
}
