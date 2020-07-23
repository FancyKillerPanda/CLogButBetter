//  ===== Date Created: 23 July, 2020 ===== 

#include "textbox.hpp"
#include "common.hpp"

TextBox::TextBox(const sf::Font& font, sf::Vector2i centrePosition, sf::Vector2i size)
	: drawableText("", font, 20), backgroundShape { (sf::Vector2f) size },
	  centrePosition(std::move(centrePosition)), size(size)
{
	SET_ORIGIN_CENTER(backgroundShape);
	backgroundShape.setPosition((sf::Vector2f) centrePosition);
	backgroundShape.setFillColor(sf::Color::White);
	backgroundShape.setOutlineColor(sf::Color::Black);

	drawableText.setFillColor(sf::Color::Black);
	drawableText.setPosition(backgroundShape.getGlobalBounds().left + 2, backgroundShape.getGlobalBounds().top);
}

void TextBox::handleMouseUp(sf::Vector2i& mousePos)
{
	bool mouseOverTextBox = backgroundShape.getGlobalBounds().contains((sf::Vector2f) mousePos);
	setActive(mouseOverTextBox);
}

void TextBox::handleTextInput(sf::Event& event)
{
	if (isActive)
	{
		if (event.text.unicode != '\b')
		{
			if (event.text.unicode != 0)
			{
				if (isSecret)
				{
					displayedText += '*';
				}
				else
				{
					displayedText += (char) event.text.unicode;
				}
				
				textValue += (char) event.text.unicode;
				drawableText.setString(displayedText);
			}
		}
		else
		{
			// Handles backspace
			if (textValue.size() > 0 && displayedText.size() > 0)
			{
				displayedText.pop_back();
				textValue.pop_back();
				drawableText.setString(displayedText);
			}
		}
	}
}

void TextBox::draw(sf::RenderTarget& target)
{
	target.draw(backgroundShape);
	target.draw(drawableText);
}

void TextBox::setActive(bool value)
{
	isActive = value;

	if (isActive)
	{
		backgroundShape.setOutlineThickness(1);
	}
	else
	{
		backgroundShape.setOutlineThickness(0);
	}
}

void TextBox::setSecret(bool value)
{
	isSecret = value;
}

const std::string& TextBox::getText()
{
	return textValue;
}
