//  ===== Date Created: 29 July, 2020 ===== 

#include <assert.h>
#include "dropdownmenu.hpp"

DropDownMenu::DropDownMenu(const sf::Font& font, const std::string& defaultText, const std::vector<std::string>& entryTexts, sf::Vector2i centrePosition)
	: defaultText(defaultText)
{
	assert(entryTexts.size() > 0);

	constexpr unsigned int buttonWidth = WINDOW_WIDTH * 20 / 100;
	constexpr unsigned int buttonHeight = WINDOW_HEIGHT * 5 / 100;

	selectedEntryButton = new Button(font, defaultText, centrePosition, sf::Vector2i { buttonWidth, buttonHeight });
	centrePosition.y += buttonHeight;

	for (const std::string& text : entryTexts)
	{
		entries.emplace_back(font, text, centrePosition, sf::Vector2i { buttonWidth, buttonHeight });
		centrePosition.y += buttonHeight;
	}
}

void DropDownMenu::reset()
{
	entrySelected = -1;
	selectedEntryButton->setText(defaultText);
	isExpanded = false;
}

void DropDownMenu::handleMouseMove(sf::Vector2i& mousePos)
{
	if (isExpanded)
	{
		for (Button& entry : entries)
		{
			entry.handleMouseMove(mousePos);
		}
	}
	else
	{
		selectedEntryButton->handleMouseMove(mousePos);
	}
}

void DropDownMenu::handleMouseDown(sf::Vector2i& mousePos)
{
	if (isExpanded)
	{
		for (Button& entry : entries)
		{
			entry.handleMouseDown(mousePos);
		}
	}
	else
	{
		selectedEntryButton->handleMouseDown(mousePos);
	}
}

void DropDownMenu::handleMouseUp()
{
	if (isExpanded)
	{
		bool clickedOnEntry = false;
		
		for (int i = 0; i < entries.size(); i++)
		{
			Button& entry = entries[i];
			
			if (entry.handleMouseUp())
			{
				entrySelected = i;
				clickedOnEntry = true;

				selectedEntryButton->setText(entry.getText());
			}
		}

		if (!clickedOnEntry)
		{
			entrySelected = -1;
			selectedEntryButton->setText(defaultText);
		}
		
		isExpanded = false;
	}
	else
	{
		if (selectedEntryButton->handleMouseUp())
		{
			isExpanded = true;
		}
	}
}

void DropDownMenu::draw(sf::RenderTarget& target)
{
	if (isExpanded)
	{
		for (Button& entry : entries)
		{
			entry.draw(target);
		}
	}
	else
	{
		selectedEntryButton->draw(target);
	}
}
