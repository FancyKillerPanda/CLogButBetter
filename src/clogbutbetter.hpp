//  ===== Date Created: 17 July, 2020 ===== 

#if !defined(CLOGBUTBETTER_HPP)
#define CLOGBUTBETTER_HPP

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "button.hpp"
#include "cadet.hpp"
#include "textbox.hpp"
#include "item.hpp"
#include "dropdownmenu.hpp"

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
	AddItemPage,
	RemoveItemPage,
	RestoreBackupPage,
};

class CLogButBetter
{
private:
	ProgramState programState = ProgramState::HomePage;

	sf::Font font;

	sf::Text titleText;
	Button* backButton = nullptr; // Needs to be pointer for delayed initialisation
	std::vector<Button> homePageButtons;
	std::vector<Button> managePageButtons;

	sf::Texture laurelTexture;
	sf::Sprite laurelSpriteLeft;
	sf::Sprite laurelSpriteRight;
	
	// Login page
	sf::Text usernameText;
	sf::Text passwordText;
	TextBox* usernameTextbox = nullptr;
	TextBox* passwordTextbox = nullptr;
	Button* loginButton = nullptr;

	// Add/remove item pages
	Button* addButton = nullptr;
	Button* removeButton = nullptr;
	DropDownMenu* typeSelectionMenu = nullptr;
	sf::Text sizeText;
	TextBox* sizeTextbox = nullptr;
	sf::Text quantityText;
	TextBox* quantityTextbox = nullptr;
	sf::Text quantityOrderedText;
	TextBox* quantityOrderedTextbox = nullptr;

	// Restore backup page
	sf::Text itemDatabaseFilepathText;
	sf::Text cadetDatabaseFilepathText;
	Button* restoreButton = nullptr;
	TextBox* cadetRestoreFilepathTextbox = nullptr;
	TextBox* itemRestoreFilepathTextbox = nullptr;

	bool cadetDatabaseIsActive = true;
	std::string cadetDatabaseFilepath = "res/cadets.csv";
	std::vector<Cadet> cadetDatabase;
	std::string itemDatabaseFilepath = "res/items.csv";
	std::vector<ItemGroup> itemDatabase;

#ifdef NDEBUG
	bool hasLoggedIn = false;
#else
	bool hasLoggedIn = true;
#endif
	
public:
	CLogButBetter();
	~CLogButBetter();
	
	void handleProgramEvent(sf::RenderWindow& window, sf::Event& event);
	void drawProgram(sf::RenderTarget& target);

private:
	void initHomePage();
	void initManagePage();
	void initLoginPage();
	void initAddRemoveItemPages();
	void initRestoreBackupPage();

	void drawCadetDatabase(sf::RenderTarget& target, sf::RectangleShape& horizontalLine, sf::RectangleShape& verticalLine);
	void drawItemDatabase(sf::RenderTarget& target, sf::RectangleShape& horizontalLine, sf::RectangleShape& verticalLine);
	
	void writeCadetsToFile(const std::string& filepath);
	void readCadetsFromFile(const std::string& filepath);
	void writeItemsToFile(const std::string& filepath);
	void readItemsFromFile(const std::string& filepath);

	std::pair<int, int> parseSizeFromString(ItemType type, const std::string& string);
};


#endif
