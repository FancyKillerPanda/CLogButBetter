//  ===== Date Created: 23 July, 2020 ===== 

#if !defined(TEXTBOX_HPP)
#define TEXTBOX_HPP

#include <string>
#include <SFML/Graphics.hpp>

/*
 * Represents a text entry field that the user can type into.
 *
 * When the TextBox isActive, key presses will be registered as input.
 * If isSecret is set, all characters will be displayed as '*'.
 * If isNumbersOnly is set, only numerical characters will be
 * accepted. All other input will be ignored.
 */
class TextBox
{
private:
	bool isActive = false;
	bool isSecret = false;
	bool isNumbersOnly = false;

	std::string displayedText;
	std::string textValue;

	sf::Text drawableText;
	sf::RectangleShape backgroundShape;
	sf::Vector2i centrePosition;
	sf::Vector2i size;

public:
	/*
	 * Constructs the TextBox object.
	 *
	 * Inputs: The font used for the text, the position of the center of the
	 * TextBox, and the dimensions of it.
	 */
	TextBox(const sf::Font& font, sf::Vector2i centrePosition, sf::Vector2i size);

	/*
	 * Clears the text in the TextBox.
	 */
	void reset();
	
	/*
	 * Handles a mouse up event.
	 * Input: The current position of the mouse cursor.
	 */
	void handleMouseUp(sf::Vector2i& mousePos);

	/*
	 * Handles a text input event.
	 * Input: The event structure that is filled in by SFML.
	 */
	void handleTextInput(sf::Event& event);

	/*
	 * Draws the TextBox to the target.
	 * Input: The target to render to.
	 */
	void draw(sf::RenderTarget& target);

	void setActive(bool value);
	void setSecret(bool value);
	void setNumbersOnly(bool value);

	const std::string& getText();
};

#endif
