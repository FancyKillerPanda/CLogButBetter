//  ===== Date Created: 15 July, 2020 ===== 

#include "button.hpp"
#include "common.hpp"

#define BUTTON_DEFAULT_COLOUR 216, 216, 216, 255
#define BUTTON_HOVER_COLOUR   190, 190, 190, 255
#define BUTTON_PRESSED_COLOUR 140, 140, 140, 255

Button::Button(const sf::Font& font, std::string text, sf::Vector2i centrePosition, sf::Vector2i size)
	: text(std::move(text)), backgroundShape { (sf::Vector2f) size },
	  centrePosition(std::move(centrePosition)), size(size)
{
	SET_ORIGIN_CENTER(backgroundShape);
	backgroundShape.setPosition((sf::Vector2f) centrePosition);
	backgroundShape.setFillColor(sf::Color { BUTTON_DEFAULT_COLOUR });

	drawableText.setString(this->text);
	drawableText.setCharacterSize(24);
	drawableText.setFont(font);
	drawableText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(drawableText);
	drawableText.setPosition((sf::Vector2f) centrePosition);
}

void Button::handleMouseMove(sf::Vector2i& mousePos)
{
	bool mouseOverButton = backgroundShape.getGlobalBounds().contains((sf::Vector2f) mousePos);
	
	if (isHot || isActive)
	{
		if (!mouseOverButton)
		{
			setHot(false);
			setActive(false);
		}
	}
	else
	{
		if (mouseOverButton)
		{
			setHot(true);
		}
	}
}

void Button::handleMouseDown(sf::Vector2i& mousePos)
{
	bool mouseOverButton = backgroundShape.getGlobalBounds().contains((sf::Vector2f) mousePos);

	if (mouseOverButton)
	{
		isActive = true;
		backgroundShape.setFillColor(sf::Color { BUTTON_PRESSED_COLOUR });
	}
}

bool Button::handleMouseUp()
{
	bool wasActive = isActive;
	setActive(false);
	
	return wasActive;
}

void Button::draw(sf::RenderTarget& target)
{
	target.draw(backgroundShape);
	target.draw(drawableText);
}

void Button::setActive(bool value)
{
	isActive = value;

	if (isActive)
	{
		backgroundShape.setFillColor(sf::Color { BUTTON_PRESSED_COLOUR });
	}
	else
	{
		// Updates the colour, but not the isHot value
		setHot(isHot);
	}
}
	
void Button::setHot(bool value)
{
	isHot = value;

	if (isHot)
	{
		backgroundShape.setFillColor(sf::Color { BUTTON_HOVER_COLOUR });	
	}
	else
	{
		backgroundShape.setFillColor(sf::Color { BUTTON_DEFAULT_COLOUR });
	}
}

void Button::setText(const std::string& newText)
{
	text = newText;
	drawableText.setString(text);

	// Resets the position
	drawableText.setOrigin(0, 0);
	drawableText.setPosition(sf::Vector2f { 0.0f, 0.0f });
	SET_ORIGIN_CENTER(drawableText);
	drawableText.setPosition((sf::Vector2f) centrePosition);
}

const std::string& Button::getText()
{
	return text;
}
