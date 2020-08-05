//  ===== Date Created: 15 July, 2020 ===== 

#if !defined(BUTTON_HPP)
#define BUTTON_HPP

#include <string>
#include <SFML/Graphics.hpp>

/*
 * Represents a button that the user can interact with.
 *
 * If isHot, the button is being hovered over. It will slightly darken.
 * If isActive, the button is being pressed. It will darken more.
 */ 
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
	/*
	 * Constructs the Button object.
	 *
	 * Inputs: The font used for the text, the text to display, the position of
	 * the center of the Button, and the dimensions of it.
	 */
	Button(const sf::Font& font, std::string text, sf::Vector2i centrePosition, sf::Vector2i size);

	/*
	 * Handles a mouse move event.
	 * Input: The current position of the mouse cursor.
	 */
	void handleMouseMove(sf::Vector2i& mousePos);
	
	/*
	 * Handles a mouse pressed event.
	 * Input: The current position of the mouse cursor.
	 */
	void handleMouseDown(sf::Vector2i& mousePos);
	
	/*
	 * Handles a mouse released event.
	 * Output: Returns true if the button was clicked, false otherwise.
	 */
	bool handleMouseUp();
	
	/*
	 * Draws the Button to the target.
	 * Input: The target to render to.
	 */
	void draw(sf::RenderTarget& target);

	void setActive(bool value);
	void setHot(bool value);
	void setText(const std::string& newText);

	const std::string& getText();
};

#endif
