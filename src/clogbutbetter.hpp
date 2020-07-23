//  ===== Date Created: 17 July, 2020 ===== 

#if !defined(CLOGBUTBETTER_HPP)
#define CLOGBUTBETTER_HPP

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "button.hpp"
#include "cadet.hpp"
#include "textbox.hpp"

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

enum ManagePageButtonIndex
{
	ADD_CADET_BUTTON,
	REMOVE_CADET_BUTTON,
	ADD_ITEM_BUTTON,
	REMOVE_ITEM_BUTTON,
	CREATE_BACKUP_BUTTON,
	RESTORE_BACKUP_BUTTON,
	GET_SIZES_BUTTON,
	
	// Keep last
	MANAGE_PAGE_BUTTON_COUNT,
};

enum class ProgramState
{
	HomePage,
	ViewDatabasePage,
	IssuesPage,
	ExchangesPage,
	ReturnsPage,
	ManagePage,
	LoginPage,
};

class CLogButBetter
{
private:
	ProgramState programState = ProgramState::HomePage;

	sf::Font font;
	sf::Text titleText;
	sf::Text usernameText;
	sf::Text passwordText;

	Button* backButton = nullptr; // Needs to be pointer for delayed initialisation
	std::vector<Button> homePageButtons;
	std::vector<Button> managePageButtons;
	
	Button* loginButton = nullptr;
	TextBox* usernameTextbox = nullptr;
	TextBox* passwordTextbox = nullptr;

	std::string cadetDatabaseFilepath = "res/cadets.csv";
	std::vector<Cadet> cadetDatabase;

	bool hasLoggedIn = false;
	
public:
	CLogButBetter();
	~CLogButBetter();
	
	void handleProgramEvent(sf::RenderWindow& window, sf::Event& event);
	void drawProgram(sf::RenderTarget& target);

private:
	void initHomePage();
	void initManagePage();
	void initLoginPage();

	void writeCadetsToFile();
	void readCadetsFromFile();
};


#endif
