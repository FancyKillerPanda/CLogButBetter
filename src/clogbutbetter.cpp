//  ===== Date Created: 17 July, 2020 ===== 

#include <fstream>
#include <string>
#include <sstream>

#include "clogbutbetter.hpp"

CLogButBetter::CLogButBetter()
{
	font.loadFromFile("res/arial.ttf");

	titleText = sf::Text { "415 Squadron Logistics System", font, 32 };
	SET_ORIGIN_CENTER(titleText);
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	titleText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 12 / 100);

	readCadetsFromFile();
	readItemsFromFile();
	
	initHomePage();
	initManagePage();
	initLoginPage();

	backButton = new Button(font, "<--",
							sf::Vector2i { WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 5 / 100},
							sf::Vector2i { WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 3 / 100});
}

CLogButBetter::~CLogButBetter()
{
	delete backButton;
	
	delete loginButton;
	delete usernameTextbox;
	delete passwordTextbox;
}

void CLogButBetter::handleProgramEvent(sf::RenderWindow& window, sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
	{
		window.close();
	} break;

	case sf::Event::MouseMoved:
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		switch (programState)
		{
		case ProgramState::HomePage:
		{
			for (Button& button : homePageButtons)
			{
				button.handleMouseMove(mousePos);
			}
		} break;
		
		case ProgramState::ManagePage:
		{
			for (Button& button : managePageButtons)
			{
				button.handleMouseMove(mousePos);
			}
		} break;

		case ProgramState::LoginPage:
		{
			loginButton->handleMouseMove(mousePos);
		} break;

		default:
		{
		} break;
		}
		
		if (programState != ProgramState::HomePage)
		{
			backButton->handleMouseMove(mousePos);
		}
	} break;

	case sf::Event::MouseButtonPressed:
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				
		switch (programState)
		{
		case ProgramState::HomePage:
		{
			for (Button& button : homePageButtons)
			{
				button.handleMouseDown(mousePos);
			}
		} break;
				
		case ProgramState::ManagePage:
		{
			for (Button& button : managePageButtons)
			{
				button.handleMouseDown(mousePos);
			}
		} break;
				
		case ProgramState::LoginPage:
		{
			loginButton->handleMouseDown(mousePos);
		} break;

		default:
		{
		} break;
		}

		if (programState != ProgramState::HomePage)
		{
			backButton->handleMouseDown(mousePos);
		}
	} break;

	case sf::Event::MouseButtonReleased:
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		
		switch (programState)
		{
		case ProgramState::HomePage:
		{
			for (unsigned int i = 0; i < HOME_PAGE_BUTTON_COUNT; i++)
			{
				if (homePageButtons[i].handleMouseUp())
				{
					switch (i)
					{
					case VIEW_CADETS_BUTTON:
					{
						programState = ProgramState::ViewDatabasePage;
					} break;
									
					case VIEW_SQUADRON_BUTTON:
					{
						programState = ProgramState::ViewDatabasePage;
					} break;
									
					case ISSUES_BUTTON:
					{
						programState = ProgramState::IssuesPage;
					} break;
									
					case EXCHANGES_BUTTON:
					{
						programState = ProgramState::ExchangesPage;
					} break;
									
					case RETURNS_BUTTON:
					{
						programState = ProgramState::ReturnsPage;
					} break;
									
					case MANAGE_BUTTON:
					{
						if (hasLoggedIn)
						{
							programState = ProgramState::ManagePage;
						}
						else
						{
							programState = ProgramState::LoginPage;
						}
					} break;
					}

					homePageButtons[i].setActive(false);
				}
			}
		} break;

		case ProgramState::ManagePage:
		{
			for (Button& button : managePageButtons)
			{
				button.handleMouseUp();
			}
		} break;
		
		case ProgramState::LoginPage:
		{
			usernameTextbox->handleMouseUp(mousePos);
			passwordTextbox->handleMouseUp(mousePos);
			
			if (loginButton->handleMouseUp())
			{
				// const std::string& username = usernameTextbox->getText();
				const std::string& password = passwordTextbox->getText();

				if (password == "415sqn")
				{
					hasLoggedIn = true;
					programState = ProgramState::ManagePage;
				}
			}
		}

		default:
		{
		} break;
		}

		if (programState != ProgramState::HomePage)
		{
			if (backButton->handleMouseUp())
			{
				programState = ProgramState::HomePage;
			}
		}
	} break;

	case sf::Event::TextEntered:
	{
		usernameTextbox->handleTextInput(event);
		passwordTextbox->handleTextInput(event);
	} break;
	
	default:
	{
	} break;
	}
}

void CLogButBetter::drawProgram(sf::RenderTarget& target)
{
	switch (programState)
	{
	case ProgramState::HomePage:
	{
		target.draw(titleText);

		for (Button& button : homePageButtons)
		{
			button.draw(target);
		}
	} break;

	case ProgramState::ViewDatabasePage:
	{
		target.draw(titleText);
		
		sf::RectangleShape background { sf::Vector2f { WINDOW_WIDTH * 90 / 100, WINDOW_HEIGHT * 75 / 100 } };
		background.setPosition(WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 20 / 100);
		background.setFillColor(sf::Color::White);
		target.draw(background);

		sf::RectangleShape horizontalLine { sf::Vector2f { tableWidth, 1 }};
		horizontalLine.setFillColor(sf::Color::Black);
		sf::RectangleShape verticalLine { sf::Vector2f { 1, tableHeight }};
		verticalLine.setFillColor(sf::Color::Black);

		if (cadetDatabaseIsActive)
		{
			drawCadetDatabase(target, horizontalLine, verticalLine);
		}
		else
		{
			drawItemDatabase(target, horizontalLine, verticalLine);
		}
	} break;

	case ProgramState::IssuesPage:
	{
		target.draw(titleText);
	} break;

	case ProgramState::ExchangesPage:
	{
		target.draw(titleText);
	} break;

	case ProgramState::ReturnsPage:
	{
		target.draw(titleText);
	} break;

	case ProgramState::ManagePage:
	{
		target.draw(titleText);

		for (Button& button : managePageButtons)
		{
			button.draw(target);
		}
	} break;

	case ProgramState::LoginPage:
	{
		target.draw(usernameText);
		usernameTextbox->draw(target);
		target.draw(passwordText);
		passwordTextbox->draw(target);
		
		loginButton->draw(target);
	} break;

	default:
	{
	} break;
	}

	if (programState != ProgramState::HomePage)
	{
		backButton->draw(target);
	}
}

void CLogButBetter::initHomePage()
{
#define HPB homePageButtons
	
	// NOTE(fkp): Volatile, initilise in order of ButtonIndex
	HPB.reserve(HOME_PAGE_BUTTON_COUNT);
	sf::Vector2i buttonSize { HOME_PAGE_BUTTON_WIDTH, HOME_PAGE_BUTTON_HEIGHT };

	HPB.emplace_back(font, "View Cadets",
					 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 40 / 100 },
					 buttonSize);
	HPB.emplace_back(font, "View Squadron",
					 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 60 / 100 },
					 buttonSize);
	HPB.emplace_back(font, "Issues",
					 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 30 / 100 },
					 buttonSize);
	HPB.emplace_back(font, "Exchanges",
					 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 50 / 100 },
					 buttonSize);
	HPB.emplace_back(font, "Returns",
					 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 70 / 100 },
					 buttonSize);
	HPB.emplace_back(font, "Manage",
					 sf::Vector2i { WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 50 / 100 },
					 buttonSize);
	
#undef HPB
}

void CLogButBetter::initManagePage()
{
#define MPB managePageButtons

	MPB.reserve(MANAGE_PAGE_BUTTON_COUNT);
	sf::Vector2i buttonSize { MANAGE_PAGE_BUTTON_WIDTH, MANAGE_PAGE_BUTTON_HEIGHT };

	MPB.emplace_back(font, "Add Cadet",
					 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 35 / 100 },
					 buttonSize);
	MPB.emplace_back(font, "Remove Cadet",
					 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 55 / 100 },
					 buttonSize);
	MPB.emplace_back(font, "Add Item",
					 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 35 / 100 },
					 buttonSize);
	MPB.emplace_back(font, "Remove Item",
					 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 55 / 100 },
					 buttonSize);
	MPB.emplace_back(font, "Create Backup",
					 sf::Vector2i { WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 35 / 100 },
					 buttonSize);
	MPB.emplace_back(font, "Restore Backup",
					 sf::Vector2i { WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 55 / 100 },
					 buttonSize);
	MPB.emplace_back(font, "Get Sizes",
					 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 75 / 100 },
					 sf::Vector2i { WINDOW_WIDTH * 30 / 100, WINDOW_HEIGHT * 10 / 100 });
		
#undef MPB
}

void CLogButBetter::initLoginPage()
{
	usernameText = sf::Text { "Username:", font, 24 };
	usernameText.setFillColor(sf::Color::Black);
	usernameText.setPosition((WINDOW_WIDTH * 50 / 100) - (usernameText.getGlobalBounds().width / 2),
							 (WINDOW_HEIGHT * 30 / 100) - (usernameText.getGlobalBounds().height / 2));
	
	usernameTextbox = new TextBox(font,
								  sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 40 / 100 },
								  sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 5 / 100 });
	usernameTextbox->setActive(true);
	passwordTextbox = new TextBox(font,
								  sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 60 / 100},
								  sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 5 / 100});
	passwordTextbox->setSecret(true);

	passwordText = sf::Text { "Password:", font, 24 };
	passwordText.setFillColor(sf::Color::Black);
	passwordText.setPosition((WINDOW_WIDTH * 50 / 100) - (passwordText.getGlobalBounds().width / 2),
							 (WINDOW_HEIGHT * 50 / 100) - (passwordText.getGlobalBounds().height / 2));
	
	loginButton = new Button(font, "Login",
							 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 70 / 100},
							 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 5 / 100 });
}

void CLogButBetter::drawCadetDatabase(sf::RenderTarget& target, sf::RectangleShape& horizontalLine, sf::RectangleShape& verticalLine)
{
	// NOTE(fkp): The +5 is just to add some padding
	constexpr unsigned int serviceNumberX = tableX + 5;
	constexpr unsigned int serviceNumberWidth = tableWidth * 15 / 100;
	constexpr unsigned int rankX = serviceNumberX + serviceNumberWidth + 5;
	constexpr unsigned int rankWidth = tableWidth * 10 / 100;
	constexpr unsigned int nameX = rankX + rankWidth + 5;
	constexpr unsigned int nameWidth = tableWidth * 25 / 100;
		
	unsigned int currentY = tableY;
	sf::Text entryText { "", font, 20 };
	entryText.setFillColor(sf::Color::Black);

	// Header row
	entryText.setStyle(sf::Text::Bold);
	entryText.setString("Service #");
	entryText.setPosition((float) serviceNumberX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Rank");
	entryText.setPosition((float) rankX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Name");
	entryText.setPosition((float) nameX, (float) currentY);
	target.draw(entryText);

	currentY += entryText.getCharacterSize() + 3;
	entryText.setStyle(sf::Text::Regular);
		
	for (Cadet& cadet : cadetDatabase)
	{
		entryText.setString(std::to_string(cadet.serviceNumber));
		entryText.setPosition((float) serviceNumberX, (float) currentY);
		target.draw(entryText);

		entryText.setString(cadet.rankAbbrev);
		entryText.setPosition((float) rankX, (float) currentY);
		target.draw(entryText);

		entryText.setString(cadet.firstName + " " + cadet.lastName);
		entryText.setPosition((float) nameX, (float) currentY);
		target.draw(entryText);

		currentY += entryText.getCharacterSize() + 2;
	}

	// Draws the grid
	verticalLine.setPosition(rankX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(nameX - 5, tableY);
	target.draw(verticalLine);

	// NOTE(fkp): +3 skips the header row, +2 for each row after
	for (int y = tableY + entryText.getCharacterSize() + 3; y < tableY + tableWidth; y += entryText.getCharacterSize() + 2)
	{
		horizontalLine.setPosition(tableX, (float) y);
		target.draw(horizontalLine);			
	}
}

void CLogButBetter::drawItemDatabase(sf::RenderTarget& target, sf::RectangleShape& horizontalLine, sf::RectangleShape& verticalLine)
{
	// NOTE(fkp): The +5 is just to add some padding
	constexpr unsigned int typeX = tableX + 5;
	constexpr unsigned int typeWidth = tableWidth * 15 / 100;
	constexpr unsigned int sizeX = typeX + typeWidth + 5;
	constexpr unsigned int sizeWidth = tableWidth * 10 / 100;
	constexpr unsigned int subsizeX = sizeX + sizeWidth + 5;
	constexpr unsigned int subsizeWidth = tableWidth * 10 / 100;
	constexpr unsigned int quantityX = subsizeX + subsizeWidth + 5;
	constexpr unsigned int quantityWidth = tableWidth * 15 / 100;
	constexpr unsigned int quantityOnOrderX = quantityX + quantityWidth + 5;
	constexpr unsigned int quantityOnOrderWidth = tableWidth * 15 / 100;
	constexpr unsigned int notesX = quantityOnOrderX + quantityOnOrderWidth + 5;
	constexpr unsigned int notesWidth = tableWidth * 35 / 100;
}

#define READ_STRING_UNTIL_COMMA(name)			\
	std::getline(line, name, ',');

#define READ_UINT_UNTIL_COMMA(name, nameStr)	\
	std::string nameStr;						\
	READ_STRING_UNTIL_COMMA(nameStr);			\
	name = std::stoul(nameStr);

#define READ_INT_UNTIL_COMMA(name, nameStr)		\
	std::string nameStr;						\
	READ_STRING_UNTIL_COMMA(nameStr);			\
	name = std::stoi(nameStr);

// NOTE(fkp): Volatile - must stay in sync with writeCadetsToFile()
void CLogButBetter::readCadetsFromFile()
{
	std::string lineStr;
	std::ifstream file { cadetDatabaseFilepath };

	if (!file)
	{
		printf("Error: Failed to open cadet database file for reading.\n");
		return;
	}

	cadetDatabase.clear();
	
	while (std::getline(file, lineStr))
	{
		std::stringstream line { lineStr };
		cadetDatabase.emplace_back();
		
		unsigned int cadetServiceNumber;
		READ_UINT_UNTIL_COMMA(cadetServiceNumber, cadetServiceNumberStr);
		cadetDatabase.back().serviceNumber = cadetServiceNumber;

		std::string cadetRank;
		READ_STRING_UNTIL_COMMA(cadetRank);
		cadetDatabase.back().rankAbbrev = cadetRank;
		
		std::string cadetFirstName;
		READ_STRING_UNTIL_COMMA(cadetFirstName);
		cadetDatabase.back().firstName = cadetFirstName;
		
		std::string cadetLastName;
		READ_STRING_UNTIL_COMMA(cadetLastName);
		cadetDatabase.back().lastName = cadetLastName;
	}
}

// NOTE(fkp): Volatile - must stay in sync with readCadetsFromFile()
void CLogButBetter::writeCadetsToFile()
{
	std::string line;
	std::ofstream file { cadetDatabaseFilepath };

	if (!file)
	{
		printf("Error: Failed to open cadet database file for writing.\n");
		return;
	}

	for (Cadet& cadet : cadetDatabase)
	{
		file << cadet.serviceNumber << ",";
		file << cadet.rankAbbrev << ",";
		file << cadet.firstName << ",";
		file << cadet.lastName << ",";

		file << "\n";
	}
}

// NOTE(fkp): Volatile - must stay in sync with writeItemsToFile()
void CLogButBetter::readItemsFromFile()
{
	std::string lineStr;
	std::ifstream file { itemDatabaseFilepath };

	if (!file)
	{
		printf("Error: Failed to open item database file for reading.\n");
		return;
	}

	itemDatabase.clear();
	
	while (std::getline(file, lineStr))
	{
		std::stringstream line { lineStr };
		itemDatabase.emplace_back();
		
		std::string itemType;
		READ_STRING_UNTIL_COMMA(itemType);
		itemDatabase.back().type = getItemTypeFromString(itemType);

		int itemSize;
		READ_INT_UNTIL_COMMA(itemSize, itemSizeStr);
		itemDatabase.back().size = itemSize;

		int itemSubsize;
		READ_INT_UNTIL_COMMA(itemSubsize, itemSubsizeStr);
		itemDatabase.back().subsize = itemSubsize;

		unsigned int itemQuantity;
		READ_UINT_UNTIL_COMMA(itemQuantity, itemQuantityStr);
		itemDatabase.back().quantity = itemQuantity;

		unsigned int itemQuantityOnOrder;
		READ_UINT_UNTIL_COMMA(itemQuantityOnOrder, itemQuantityOnOrderStr);
		itemDatabase.back().quantityOnOrder = itemQuantityOnOrder;

		std::string itemNotes;
		READ_STRING_UNTIL_COMMA(itemNotes);
		itemDatabase.back().notes = itemNotes;
	}
}

// NOTE(fkp): Volatile - must stay in sync with readItemsFromFile()
void CLogButBetter::writeItemsToFile()
{
	std::string line;
	std::ofstream file { itemDatabaseFilepath };

	if (!file)
	{
		printf("Error: Failed to open item database file for writing.\n");
		return;
	}

	for (ItemGroup& item : itemDatabase)
	{
		file << getStringFromItemType(item.type) << ",";
		file << item.size << ",";
		file << item.subsize << ",";
		file << item.quantity << ",";
		file << item.quantityOnOrder << ",";
		file << item.notes << ",";
		
		file << "\n";
	}
}
