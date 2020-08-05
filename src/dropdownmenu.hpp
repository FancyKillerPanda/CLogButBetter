//  ===== Date Created: 29 July, 2020 ===== 

#if !defined(DROPDOWNMENU_HPP)
#define DROPDOWNMENU_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "button.hpp"

/*
 * Represents a drop down menu that the user can interact with.

 * When the menu is clicked once, isExpanded will be set and the options
 * available will be shown. On the next mouse up event, it either selects
 * one of those options or resets the menu to its original state.
 */
class DropDownMenu
{
private:
	bool isExpanded = false;

	std::string defaultText = "";
	std::vector<Button> entries;
	Button* selectedEntryButton = nullptr;
	int entrySelected = -1;

public:
	/*
	 * Constructs is DropDownMenu object.

	 * Inputs: The font used for the text, the default text to be shown,
	 * an array of texts to be shown as possible options, and the position
	 * of the center of the main button.
	 */
	DropDownMenu(const sf::Font& font, const std::string& defaultText, const std::vector<std::string>& entryTexts, sf::Vector2i centrePosition);

	/*
	 * Resets the menu to its original, non-expanded state with nothing selected.
	 */
	void reset();
	
	/*
	 * Handles a mouse movement event.
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
	 */
	void handleMouseUp();

	/*
	 * Draws the menu to the target.
	 * Input: The target to render to.
	 */
	void draw(sf::RenderTarget& target);

	int getSelectedEntry() { return entrySelected; }
	Button* getSelectedButton() { return selectedEntryButton; };
};

#endif
