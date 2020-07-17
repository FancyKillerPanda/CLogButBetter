//  ===== Date Created: 17 July, 2020 ===== 

#if !defined(CLOGBUTBETTER_HPP)
#define CLOGBUTBETTER_HPP

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "button.hpp"

// Will be used to access buttons in the vector. Rather than using a
// plain index, these names help to understand which button is being
// accessed.
enum HomePageButtonIndex
{
	VIEW_CADETS_BUTTON,
	VIEW_SQUADRON_BUTTON,
	ISSUES_BUTTON,
	EXCHANGES_BUTTON,
	RETURNS_BUTTON,
	MANAGE_BUTTON,

	// Keep last
	HOME_PAGE_BUTTON_COUNT,
};

enum class ProgramState
{
	HomePage,
	ViewDatabasePage,
	IssuesPage,
	ExchangesPage,
	ReturnsPage,
	ManagePage,
};

class CLogButBetter
{
private:
	ProgramState programState = ProgramState::HomePage;
	sf::Font font;

	sf::Text titleText;
	std::vector<Button> homePageButtons;
	
public:
	CLogButBetter();	
	
	void handleProgramEvent(sf::RenderWindow& window, sf::Event& event);
	void drawProgram(sf::RenderTarget& target);

private:
	void initHomePageButtons();
};


#endif
