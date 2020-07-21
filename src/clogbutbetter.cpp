//  ===== Date Created: 17 July, 2020 ===== 

#include <fstream>
#include <string>

#include "clogbutbetter.hpp"

CLogButBetter::CLogButBetter()
{
	font.loadFromFile("res/arial.ttf");

	titleText = sf::Text { "415 Squadron Logistics System", font, 32 };
	SET_ORIGIN_CENTER(titleText);
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	titleText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 12 / 100);

	initHomePageButtons();
	initManagePageButtons();

	backButton = new Button(font, "<--",
							sf::Vector2i { WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 5 / 100},
							sf::Vector2i { WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 3 / 100});
}

CLogButBetter::~CLogButBetter()
{
	delete backButton;
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
						programState = ProgramState::ManagePage;
					} break;
					}
				}
			}
		} break;

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

	default:
	{
	} break;
	}

	if (programState != ProgramState::HomePage)
	{
		backButton->draw(target);
	}
}

void CLogButBetter::initHomePageButtons()
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

void CLogButBetter::initManagePageButtons()
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

#define READ_STRING_UNTIL_COMMA(name)			\
	std::getline(file, name, ',');

#define READ_UINT_UNTIL_COMMA(name, nameStr)	\
	std::string nameStr;						\
	READ_STRING_UNTIL_COMMA(nameStr);			\
	name = std::stoul(nameStr);

// NOTE(fkp): Volatile - must stay in sync with writeCadetsToFile()
void CLogButBetter::readCadetsFromFile()
{
	std::string line;
	std::ifstream file { cadetDatabaseFilepath };

	if (!file)
	{
		printf("Error: Failed to open cadet database file for reading.\n");
		return;
	}

	cadetDatabase.clear();
	
	while (std::getline(file, line))
	{
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
