//  ===== Date Created: 29 July, 2020 ===== 

#if !defined(DROPDOWNMENU_HPP)
#define DROPDOWNMENU_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "button.hpp"

class DropDownMenu
{
private:
	bool isExpanded = false;

	std::string defaultText = "";
	std::vector<Button> entries;
	Button* selectedEntryButton = nullptr;
	int entrySelected = -1;

public:
	DropDownMenu(const sf::Font& font, const std::string& defaultText, const std::vector<std::string>& entryTexts, sf::Vector2i centrePosition);

	void handleMouseMove(sf::Vector2i& mousePos);
	void handleMouseDown(sf::Vector2i& mousePos);
	void handleMouseUp();
	void draw(sf::RenderTarget& target);

	int getSelectedEntry() { return entrySelected; }
	Button* getSelectedButton() { return selectedEntryButton; };
};

#endif
