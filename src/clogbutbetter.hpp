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

/*
 * Holds indices into the vector of buttons on the home page.
 *
 * Will be used to access buttons in the vector. Rather than using a
 * plain index, these names help to understand which button is being
 * accessed.
 */
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

/*
 * Holds indices into the vector of buttons on the manage page.
 */
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

/*
 * Holds indices into the vector of UI elements on the get-sizes page.
 */
enum GetSizesPageIndex
{
	CHEST_SIZE_INDEX,
	HEAD_SIZE_INDEX,
	NECK_SIZE_INDEX,
	SLEEVE_SIZE_INDEX,
	WAIST_SIZE_INDEX,
	INSEAM_SIZE_INDEX,
	HEIGHT_SIZE_INDEX,
	SHOE_SIZE_INDEX,

	// Keep last
	GET_SIZES_INDEX_COUNT
};

/*
 * Holds the current page that the program is in.
 */
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
	AddCadetPage,
	RemoveCadetPage,
	CreateBackupPage,
	RestoreBackupPage,
	GetSizesPage,
	ViewSizesPage,
};

/*
 * The field to sort the items database by.
 */
enum class ItemField
{
	Type,
	Size,
	Quantity,
	QuantityOnOrder,
};

/*
 * The main class of the project, this connects everything together.
 */
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
	Button* addItemButton = nullptr;
	Button* removeItemButton = nullptr;
	DropDownMenu* typeSelectionMenu = nullptr;
	sf::Text sizeText;
	TextBox* sizeTextbox = nullptr;
	sf::Text quantityText;
	TextBox* quantityTextbox = nullptr;
	sf::Text quantityOrderedText;
	TextBox* quantityOrderedTextbox = nullptr;

	// Add/remove cadet pages
	Button* addCadetButton = nullptr;
	Button* removeCadetButton = nullptr;
	sf::Text serviceNumberText;
	TextBox* serviceNumberTextbox = nullptr;
	sf::Text rankText;
	TextBox* rankTextbox = nullptr;
	sf::Text nameText;
	TextBox* nameTextbox = nullptr;

	// Create/restore backup pages
	Button* createBackupButton = nullptr;
	Button* restoreBackupButton = nullptr;
	sf::Text itemDatabaseFilepathText;
	sf::Text cadetDatabaseFilepathText;
	TextBox* cadetRestoreFilepathTextbox = nullptr;
	TextBox* itemRestoreFilepathTextbox = nullptr;

	// Get/view sizes page
	Button* calculateSizesButton = nullptr;
	std::vector<sf::Text> getSizesPageTexts;
	std::vector<TextBox> getSizesPageTextboxes;
	std::vector<sf::Text> viewSizesPageTexts;

	// The databases holding all cadet and item information
	bool cadetDatabaseIsActive = true;
	std::string cadetDatabaseFilepath = "res/cadets.csv";
	std::vector<Cadet> cadetDatabase;
	std::vector<Cadet> cadetDatabaseShown; // What is displayed, after searching
	std::string itemDatabaseFilepath = "res/items.csv";
	std::vector<ItemGroup> itemDatabase;

	// Search bar
	TextBox* searchTextbox = nullptr;

	// Used to skip the login page when debugging.
#ifdef NDEBUG
	bool hasLoggedIn = false;
#else
	bool hasLoggedIn = true;
#endif
	
public:
	/*
	 * Constructs the object.
	 */
	CLogButBetter();

	/*
	 * Destructs the object.
	 */
	~CLogButBetter();
	
	/*
	 * Handles a single event polled from SFML.
	 * Input: The window that polled the event, the event itself.
	 */
	void handleProgramEvent(sf::RenderWindow& window, sf::Event& event);

	/*
	 * Draws the entire program to the target.
	 * This method will dispatch to other draw calls.
	 *
	 * Input: The target to draw to.
	 */
	void drawProgram(sf::RenderTarget& target);

private:
	/*
	 * Initialisation helper methods.
	 * These are called from the constructor of the object.
	 */
	void initHomePage();
	void initManagePage();
	void initLoginPage();
	void initAddRemoveItemPages();
	void initAddRemoveCadetPages();
	void initBackupPages();
	void initGetSizesPage();

	/*
	 * Draws the database view for cadets and items.
	 * The reason these are separate methods is that they require different layouts,
	 * although they do very similar things.
	 *
	 * Inputs: The target to draw to, a horizontal line that can be drawn, and a
	 * vertical line that can be draw.
	 */
	void drawCadetDatabase(sf::RenderTarget& target, sf::RectangleShape& horizontalLine, sf::RectangleShape& verticalLine);
	void drawItemDatabase(sf::RenderTarget& target, sf::RectangleShape& horizontalLine, sf::RectangleShape& verticalLine);
	
	/*
	 * Writes the databases to files.
	 * Input: Filepath that the database will be written to.
	 */
	void writeCadetsToFile(const std::string& filepath);
	void writeItemsToFile(const std::string& filepath);
	
	/*
	 * Reads the databases from files.
	 * Input: Filepath that the database will be read from.
	 */
	void readCadetsFromFile(const std::string& filepath);
	void readItemsFromFile(const std::string& filepath);

	/*
	 * Parses a string representation of a size into its size/subsize components.
	 *
	 * Inputs: The type of item the size represents, the string representing the size.
	 * Output: A pair of integers, the first representing the size of the item, the
	 * second representing the subsize (if it exists, else -1).
	 */
	std::pair<int, int> parseSizeFromString(ItemType type, const std::string& string);

	/*
	 * Sorts the items database by a field.
	 *
	 * Input: The field to sort by.
	 */
	void sortItemsDatabase(ItemField field);
};

/*
 * Rounds a number up to the nearest interval.
 *
 * Input: The number to round, the interval to round to.
 * Output: A rounded number that is a multiple of the interval and
 * is greater than the original number.
 */
inline int roundUp(int number, int interval)
{
	if (interval == 0)
		return number;

	int remainder = number % interval;

	if (remainder == 0)
		return number;

	return number + interval - remainder;
}

#endif
