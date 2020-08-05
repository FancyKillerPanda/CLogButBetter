//  ===== Date Created: 17 July, 2020 ===== 

#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "clogbutbetter.hpp"

CLogButBetter::CLogButBetter()
{
	font.loadFromFile("res/arial.ttf");

	titleText = sf::Text { "415 Squadron Logistics System", font, 32 };
	SET_ORIGIN_CENTER(titleText);
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	titleText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 12 / 100);

	// Loads laurel sprites
	laurelTexture.loadFromFile("res/laurel.png");
	
	laurelSpriteLeft.setTexture(laurelTexture);
	SET_ORIGIN_CENTER(laurelSpriteLeft);
	laurelSpriteLeft.setScale(sf::Vector2f { -0.25f, 0.25f });
	laurelSpriteLeft.setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 80 / 100);
	
	laurelSpriteRight.setTexture(laurelTexture);
	SET_ORIGIN_CENTER(laurelSpriteRight);
	laurelSpriteRight.setScale(sf::Vector2f { 0.25f, 0.25f });
	laurelSpriteRight.setPosition(WINDOW_WIDTH * 85 / 100, WINDOW_HEIGHT * 80 / 100);
	
	readCadetsFromFile(cadetDatabaseFilepath);
	readItemsFromFile(itemDatabaseFilepath);
	
	initHomePage();
	initManagePage();
	initLoginPage();
	initAddRemoveItemPages();
	initBackupPages();
	initGetSizesPage();

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

		case ProgramState::AddItemPage:
		{
			typeSelectionMenu->handleMouseMove(mousePos);
			addButton->handleMouseMove(mousePos);
		} break;

		case ProgramState::RemoveItemPage:
		{
			typeSelectionMenu->handleMouseMove(mousePos);
			removeButton->handleMouseMove(mousePos);
		} break;

		case ProgramState::CreateBackupPage:
		{
			createBackupButton->handleMouseMove(mousePos);
		} break;
		
		case ProgramState::RestoreBackupPage:
		{
			restoreBackupButton->handleMouseMove(mousePos);
		} break;

		case ProgramState::GetSizesPage:
		{
			calculateSizesButton->handleMouseMove(mousePos);
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

		case ProgramState::AddItemPage:
		{
			typeSelectionMenu->handleMouseDown(mousePos);
			addButton->handleMouseDown(mousePos);
		} break;

		case ProgramState::RemoveItemPage:
		{
			typeSelectionMenu->handleMouseDown(mousePos);
			removeButton->handleMouseDown(mousePos);
		} break;
		
		case ProgramState::CreateBackupPage:
		{
			createBackupButton->handleMouseDown(mousePos);
		} break;
		
		case ProgramState::RestoreBackupPage:
		{
			restoreBackupButton->handleMouseDown(mousePos);
		} break;

		case ProgramState::GetSizesPage:
		{
			calculateSizesButton->handleMouseDown(mousePos);
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
						cadetDatabaseIsActive = true;
					} break;
									
					case VIEW_SQUADRON_BUTTON:
					{
						programState = ProgramState::ViewDatabasePage;
						cadetDatabaseIsActive = false;
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
			for (int i = 0; i < managePageButtons.size(); i++)
			{
				Button& button = managePageButtons[i];
				
				if (button.handleMouseUp())
				{
					switch (i)
					{
					case ADD_ITEM_BUTTON:
					{
						programState = ProgramState::AddItemPage;
					} break;

					case REMOVE_ITEM_BUTTON:
					{
						programState = ProgramState::RemoveItemPage;
					} break;

					case CREATE_BACKUP_BUTTON:
					{
						programState = ProgramState::CreateBackupPage;
					} break;
					
					case RESTORE_BACKUP_BUTTON:
					{
						programState = ProgramState::RestoreBackupPage;
					} break;

					case GET_SIZES_BUTTON:
					{
						programState = ProgramState::GetSizesPage;
					} break;
					}
				}
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

		case ProgramState::CreateBackupPage:
		{
			cadetRestoreFilepathTextbox->handleMouseUp(mousePos);
			itemRestoreFilepathTextbox->handleMouseUp(mousePos);

			if (createBackupButton->handleMouseUp() &&
				cadetRestoreFilepathTextbox->getText() != "" &&
				itemRestoreFilepathTextbox->getText() != "")
			{
				writeCadetsToFile(cadetRestoreFilepathTextbox->getText());
				writeItemsToFile(itemRestoreFilepathTextbox->getText());

				cadetRestoreFilepathTextbox->reset();
				itemRestoreFilepathTextbox->reset();
			}
		} break;

		case ProgramState::RestoreBackupPage:
		{
			cadetRestoreFilepathTextbox->handleMouseUp(mousePos);
			itemRestoreFilepathTextbox->handleMouseUp(mousePos);

			if (restoreBackupButton->handleMouseUp() &&
				cadetRestoreFilepathTextbox->getText() != "" &&
				itemRestoreFilepathTextbox->getText() != "")
			{
				readCadetsFromFile(cadetRestoreFilepathTextbox->getText());
				readItemsFromFile(itemRestoreFilepathTextbox->getText());

				// Overwrites the normal database files so future instances will read it
				writeCadetsToFile(cadetDatabaseFilepath);
				writeItemsToFile(itemDatabaseFilepath);

				cadetRestoreFilepathTextbox->reset();
				itemRestoreFilepathTextbox->reset();
				
				programState = ProgramState::ManagePage;
			}
		} break;

		case ProgramState::AddItemPage:
		case ProgramState::RemoveItemPage:
		{
			typeSelectionMenu->handleMouseUp();

			if ((programState == ProgramState::AddItemPage && addButton->handleMouseUp()) ||
				(programState == ProgramState::RemoveItemPage && removeButton->handleMouseUp()))
			{
				if (typeSelectionMenu->getSelectedEntry() != -1 &&
					sizeTextbox->getText() != "" &&
					quantityTextbox->getText() != "" &&
					quantityOrderedTextbox->getText() != "")
				{
					ItemType type = getItemTypeFromString(typeSelectionMenu->getSelectedButton()->getText());
					auto [size, subsize] = parseSizeFromString(type, sizeTextbox->getText());
					bool found = false;

					for (ItemGroup& item : itemDatabase)
					{
						if (item.type == type &&
							item.size == size &&
							(item.subsize == -1 || item.subsize == subsize))
						{
							if (programState == ProgramState::AddItemPage)
							{
								item.quantity += std::stoi(quantityTextbox->getText());
								item.quantityOnOrder += std::stoi(quantityOrderedTextbox->getText());
							}
							else if (programState == ProgramState::RemoveItemPage)
							{
								unsigned int amountToRemove = std::stoi(quantityTextbox->getText());
								unsigned int amountToRemoveOrder = std::stoi(quantityOrderedTextbox->getText());
								
								if (amountToRemove > item.quantity)
								{
									item.quantity = 0;
								}
								else
								{
									item.quantity -= amountToRemove;
								}
								
								if (amountToRemoveOrder > item.quantityOnOrder)
								{
									item.quantityOnOrder = 0;
								}
								else
								{
									item.quantityOnOrder -= amountToRemoveOrder;
								}
							}
							
							found = true;
							break;
						}
					}

					if (!found)
					{
						if (programState == ProgramState::AddItemPage)
						{
							ItemGroup group;
							group.type = type;
							group.size = size;
							group.subsize = subsize;
							group.quantity = std::stoi(quantityTextbox->getText());
							group.quantityOnOrder = std::stoi(quantityOrderedTextbox->getText());

							itemDatabase.emplace_back(std::move(group));
						}
						else
						{
							MessageBox(nullptr, "Item to remove not found.", nullptr, MB_OK);
						}
					}

					typeSelectionMenu->reset();
					sizeTextbox->reset();
					quantityTextbox->reset();
					quantityOrderedTextbox->reset();
				}
				else
				{
					MessageBox(nullptr, "Please fill all details.", nullptr, MB_OK);
				}
			}
			
			sizeTextbox->handleMouseUp(mousePos);
			quantityTextbox->handleMouseUp(mousePos);
			quantityOrderedTextbox->handleMouseUp(mousePos);
		} break;

		case ProgramState::GetSizesPage:
		{
			for (TextBox& textbox : getSizesPageTextboxes)
			{
				textbox.handleMouseUp(mousePos);
			}

			if (calculateSizesButton->handleMouseUp())
			{
				// TODO(fkp): Calculate the sizes
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

	case sf::Event::TextEntered:
	{
		switch (programState)
		{
		case ProgramState::LoginPage:
		{
			usernameTextbox->handleTextInput(event);
			passwordTextbox->handleTextInput(event);
		} break;

		case ProgramState::CreateBackupPage:
		case ProgramState::RestoreBackupPage:
		{
			cadetRestoreFilepathTextbox->handleTextInput(event);
			itemRestoreFilepathTextbox->handleTextInput(event);
		} break;

		case ProgramState::AddItemPage:
		case ProgramState::RemoveItemPage:
		{
			sizeTextbox->handleTextInput(event);
			quantityTextbox->handleTextInput(event);
			quantityOrderedTextbox->handleTextInput(event);
		} break;
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
		target.draw(laurelSpriteLeft);
		target.draw(laurelSpriteRight);

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

	case ProgramState::AddItemPage:
	case ProgramState::RemoveItemPage:
	{
		if (programState == ProgramState::AddItemPage)
		{
			addButton->draw(target);
		}
		else if (programState == ProgramState::RemoveItemPage)
		{
			removeButton->draw(target);
		}
		
		typeSelectionMenu->draw(target);

		target.draw(sizeText);
		target.draw(quantityText);
		target.draw(quantityOrderedText);
		
		sizeTextbox->draw(target);
		quantityTextbox->draw(target);
		quantityOrderedTextbox->draw(target);
	} break;

	case ProgramState::CreateBackupPage:
	case ProgramState::RestoreBackupPage:
	{
		if (programState == ProgramState::CreateBackupPage)
		{
			createBackupButton->draw(target);
		}
		else if (programState == ProgramState::RestoreBackupPage)
		{
			restoreBackupButton->draw(target);
		}
		
		cadetRestoreFilepathTextbox->draw(target);
		itemRestoreFilepathTextbox->draw(target);
		target.draw(cadetDatabaseFilepathText);
		target.draw(itemDatabaseFilepathText);
	} break;

	case ProgramState::GetSizesPage:
	{
		calculateSizesButton->draw(target);
		
		for (sf::Text& text : getSizesPageTexts)
		{
			target.draw(text);
		}

		for (TextBox& textbox : getSizesPageTextboxes)
		{
			textbox.draw(target);
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
							 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 70 / 100 },
							 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 5 / 100 });
}

void CLogButBetter::initAddRemoveItemPages()
{
	addButton = new Button(font, "Add",
						   sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 60 / 100 },
						   sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });
	
	removeButton = new Button(font, "Remove",
							  sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 60 / 100 },
							  sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });
	
	typeSelectionMenu = new DropDownMenu(font, "Type?", { "LSSD Shirt", "SSSD Shirt",
														  "SD Trousers", "SD Jumper",
														  "SD Belt", "SD Shoes",
														  "DPU Shirt", "DPU Pants",
														  "DPU Jumper", "DPU Boots",
														  "HFFK", "Hat Badge",
														  "Puggaree", "Bush Hat",
														  "Rank Slides", "Webbing",
														  "Japara" },
										 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });

	
	sizeText = sf::Text { "Size:", font, 24 };
	sizeText.setFillColor(sf::Color::Black);
	sizeText.setPosition((WINDOW_WIDTH * 40 / 100) - (sizeText.getGlobalBounds().width / 2),
						 (WINDOW_HEIGHT * 10 / 100) - (sizeText.getGlobalBounds().height / 2));
	
	quantityText = sf::Text { "Quantity:", font, 24 };
	quantityText.setFillColor(sf::Color::Black);
	quantityText.setPosition((WINDOW_WIDTH * 60 / 100) - (quantityText.getGlobalBounds().width / 2),
							 (WINDOW_HEIGHT * 10 / 100) - (quantityText.getGlobalBounds().height / 2));
	
	quantityOrderedText = sf::Text { "Quantity Ordered:", font, 24 };
	quantityOrderedText.setFillColor(sf::Color::Black);
	quantityOrderedText.setPosition((WINDOW_WIDTH * 80 / 100) - (quantityOrderedText.getGlobalBounds().width / 2),
									(WINDOW_HEIGHT * 10 / 100) - (quantityOrderedText.getGlobalBounds().height / 2));
	
	sizeTextbox = new TextBox(font,
							  sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 20 / 100 },
							  sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 5 / 100 });
	
	quantityTextbox = new TextBox(font,
								  sf::Vector2i { WINDOW_WIDTH * 60 / 100, WINDOW_HEIGHT * 20 / 100 },
								  sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 5 / 100 });
	quantityTextbox->setNumbersOnly(true);
	
	quantityOrderedTextbox = new TextBox(font,
										 sf::Vector2i { WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 20 / 100 },
										sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 5 / 100 });
	quantityOrderedTextbox->setNumbersOnly(true);
}

void CLogButBetter::initBackupPages()
{
	restoreBackupButton = new Button(font, "Restore",
									 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 70 / 100 },
									 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 5 / 100 });

	createBackupButton = new Button(font, "Create",
									sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 70 / 100 },
									sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 5 / 100 });

	cadetDatabaseFilepathText = sf::Text { "Cadet Database File Path:", font, 24 };
	cadetDatabaseFilepathText.setFillColor(sf::Color::Black);
	cadetDatabaseFilepathText.setPosition((WINDOW_WIDTH * 50 / 100) - (cadetDatabaseFilepathText.getGlobalBounds().width / 2),
										  (WINDOW_HEIGHT * 30 / 100) - (cadetDatabaseFilepathText.getGlobalBounds().height / 2));
	
	cadetRestoreFilepathTextbox = new TextBox(font,
											  sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 40 / 100 },
											  sf::Vector2i { WINDOW_WIDTH * 60 / 100, WINDOW_HEIGHT * 5 / 100 });
	cadetRestoreFilepathTextbox->setActive(true);

	itemDatabaseFilepathText = sf::Text { "Item Database File Path:", font, 24 };
	itemDatabaseFilepathText.setFillColor(sf::Color::Black);
	itemDatabaseFilepathText.setPosition((WINDOW_WIDTH * 50 / 100) - (itemDatabaseFilepathText.getGlobalBounds().width / 2),
										 (WINDOW_HEIGHT * 50 / 100) - (itemDatabaseFilepathText.getGlobalBounds().height / 2));
	
	itemRestoreFilepathTextbox = new TextBox(font,
											 sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 60 / 100 },
											 sf::Vector2i { WINDOW_WIDTH * 60 / 100, WINDOW_HEIGHT * 5 / 100 });
}

void CLogButBetter::initGetSizesPage()
{
	calculateSizesButton = new Button(font, "Calculate",
									  sf::Vector2i { WINDOW_WIDTH * 75 / 100, WINDOW_HEIGHT * 50 / 100},
									  sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_WIDTH * 5 / 100 });
	
	getSizesPageTexts.emplace_back("Chest (cm):", font, 24);
	getSizesPageTexts.back().setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(getSizesPageTexts.back());
	getSizesPageTexts.back().setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 15 / 100);

	getSizesPageTextboxes.emplace_back(font,
									   sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 15 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	getSizesPageTextboxes.back().setNumbersOnly(true);
	getSizesPageTextboxes.back().setActive(true);
	
	getSizesPageTexts.emplace_back("Head (cm):", font, 24);
	getSizesPageTexts.back().setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(getSizesPageTexts.back());
	getSizesPageTexts.back().setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 25 / 100);

	getSizesPageTextboxes.emplace_back(font,
									   sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 25 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	getSizesPageTextboxes.back().setNumbersOnly(true);

	getSizesPageTexts.emplace_back("Neck (cm):", font, 24);
	getSizesPageTexts.back().setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(getSizesPageTexts.back());
	getSizesPageTexts.back().setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 35 / 100);

	getSizesPageTextboxes.emplace_back(font,
									   sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 35 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	getSizesPageTextboxes.back().setNumbersOnly(true);

	getSizesPageTexts.emplace_back("Sleeve (cm):", font, 24);
	getSizesPageTexts.back().setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(getSizesPageTexts.back());
	getSizesPageTexts.back().setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 45 / 100);

	getSizesPageTextboxes.emplace_back(font,
									   sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 45 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	getSizesPageTextboxes.back().setNumbersOnly(true);

	getSizesPageTexts.emplace_back("Waist (cm):", font, 24);
	getSizesPageTexts.back().setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(getSizesPageTexts.back());
	getSizesPageTexts.back().setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 55 / 100);

	getSizesPageTextboxes.emplace_back(font,
									   sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 55 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	getSizesPageTextboxes.back().setNumbersOnly(true);

	getSizesPageTexts.emplace_back("Inseam (cm):", font, 24);
	getSizesPageTexts.back().setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(getSizesPageTexts.back());
	getSizesPageTexts.back().setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 65 / 100);

	getSizesPageTextboxes.emplace_back(font,
									   sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 65 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	getSizesPageTextboxes.back().setNumbersOnly(true);

	getSizesPageTexts.emplace_back("Height (cm):", font, 24);
	getSizesPageTexts.back().setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(getSizesPageTexts.back());
	getSizesPageTexts.back().setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 75 / 100);

	getSizesPageTextboxes.emplace_back(font,
									   sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 75 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	getSizesPageTextboxes.back().setNumbersOnly(true);

	getSizesPageTexts.emplace_back("Shoe Size:", font, 24);
	getSizesPageTexts.back().setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(getSizesPageTexts.back());
	getSizesPageTexts.back().setPosition(WINDOW_WIDTH * 15 / 100, WINDOW_HEIGHT * 85 / 100);

	getSizesPageTextboxes.emplace_back(font,
									   sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 85 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	getSizesPageTextboxes.back().setNumbersOnly(true);

#undef CENTER_X
#undef CENTER_Y
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
	constexpr unsigned int typeWidth = tableWidth * 20 / 100;
	constexpr unsigned int sizeX = typeX + typeWidth + 5;
	constexpr unsigned int sizeWidth = tableWidth * 10 / 100;
	constexpr unsigned int quantityX = sizeX + sizeWidth + 5;
	constexpr unsigned int quantityWidth = tableWidth * 15 / 100;
	constexpr unsigned int quantityOnOrderX = quantityX + quantityWidth + 5;
	constexpr unsigned int quantityOnOrderWidth = tableWidth * 15 / 100;
	constexpr unsigned int notesX = quantityOnOrderX + quantityOnOrderWidth + 5;
	constexpr unsigned int notesWidth = tableWidth * 35 / 100;

	unsigned int currentY = tableY;
	sf::Text entryText { "", font, 20 };
	entryText.setFillColor(sf::Color::Black);

	// Header row
	entryText.setStyle(sf::Text::Bold);
	entryText.setString("Type");
	entryText.setPosition((float) typeX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Size");
	entryText.setPosition((float) sizeX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Quantity");
	entryText.setPosition((float) quantityX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Ordered");
	entryText.setPosition((float) quantityOnOrderX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Notes");
	entryText.setPosition((float) notesX, (float) currentY);
	target.draw(entryText);

	currentY += entryText.getCharacterSize() + 3;
	entryText.setStyle(sf::Text::Regular);
	
	for (ItemGroup& item : itemDatabase)
	{
		entryText.setString(getStringFromItemType(item.type));
		entryText.setPosition((float) typeX, (float) currentY);
		target.draw(entryText);

		if (item.type == ItemType::SD_LongSleeve)
		{
			entryText.setString(std::to_string(item.size) + "/" + std::to_string(item.subsize));
		}
		else if (item.type == ItemType::SD_Trousers || item.type == ItemType::DPU_Pants)
		{
			if (item.subsize == 0)
			{
				entryText.setString(std::to_string(item.size) + "S");
			}
			else if (item.subsize == 1)
			{
				entryText.setString(std::to_string(item.size) + "R");
			}
			else if (item.subsize == 2)
			{
				entryText.setString(std::to_string(item.size) + "L");
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			entryText.setString(std::to_string(item.size));
		}
		
		entryText.setPosition((float) sizeX, (float) currentY);
		target.draw(entryText);

		entryText.setString(std::to_string(item.quantity));
		entryText.setPosition((float) quantityX, (float) currentY);
		target.draw(entryText);

		entryText.setString(std::to_string(item.quantityOnOrder));
		entryText.setPosition((float) quantityOnOrderX, (float) currentY);
		target.draw(entryText);

		entryText.setString(item.notes);
		entryText.setPosition((float) notesX, (float) currentY);
		target.draw(entryText);

		currentY += entryText.getCharacterSize() + 2;
	}

	// Draws the grid
	verticalLine.setPosition(sizeX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(quantityX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(quantityOnOrderX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(notesX - 5, tableY);
	target.draw(verticalLine);

	// NOTE(fkp): +3 skips the header row, +2 for each row after
	for (int y = tableY + entryText.getCharacterSize() + 3; y < tableY + tableWidth; y += entryText.getCharacterSize() + 2)
	{
		horizontalLine.setPosition(tableX, (float) y);
		target.draw(horizontalLine);			
	}
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
void CLogButBetter::readCadetsFromFile(const std::string& filepath)
{
	std::string lineStr;
	std::ifstream file { filepath };

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
void CLogButBetter::writeCadetsToFile(const std::string& filepath)
{
	std::string line;
	std::ofstream file { filepath };

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
void CLogButBetter::readItemsFromFile(const std::string& filepath)
{
	std::string lineStr;
	std::ifstream file { filepath };

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
void CLogButBetter::writeItemsToFile(const std::string& filepath)
{
	std::string line;
	std::ofstream file { filepath };

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

std::pair<int, int> CLogButBetter::parseSizeFromString(ItemType type, const std::string& string)
{
	int size = -1;
	int subsize = -1;
	
	switch (type)
	{
	case ItemType::SD_LongSleeve:
	{
		size = std::stoi(string.substr(0, string.find_first_of("/")));
		subsize = std::stoi(string.substr(string.find_first_of("/") + 1));
	} return std::make_pair(size, subsize);

	case ItemType::SD_Trousers:
	case ItemType::DPU_Pants:
	{
		size = std::stoi(string.substr(0, string.size() - 1));
		subsize = 0;

		switch (string.back())
		{
		case 'S': subsize = 0; break;
		case 'R': subsize = 1; break;
		case 'L': subsize = 2; break;
		default: printf("Error: Subsize not valid.\n");
		}
	} return std::make_pair(size, subsize);

	case ItemType::SD_Jumper:
	case ItemType::DPU_Jumper:
	{
		size = std::stoi(string.substr(0, string.find_first_of("-")));
		subsize = std::stoi(string.substr(string.find_first_of("-") + 1));
	} return std::make_pair(size, subsize);
	
	case ItemType::RankSlide:
	{
		size = 0;

		if (string == "CDT") size = 0;
		else if (string == "LCDT") size = 1;
		else if (string == "CCPL") size = 2;
		else if (string == "CSGT") size = 3;
		else if (string == "CFSGT") size = 4;
		else if (string == "CWOFF") size = 5;
		else if (string == "CUO") size = 6;
		else if (string == "A/CCPL") size = 7;
		else
		{
			printf("Error: Unknown rank.\n");
		}
	} return std::make_pair(size, -1);
	
	case ItemType::SD_ShortSleeve:
	case ItemType::SD_Shoes:
	case ItemType::DPU_Shirt:
	case ItemType::DPU_Boots:
	case ItemType::Hat_HFFK:
	case ItemType::Hat_Puggaree:
	{
	} return std::make_pair(std::stoi(string), -1);

	case ItemType::SD_Belt:
	case ItemType::Hat_Badge:
	case ItemType::Hat_Bush:
	case ItemType::Webbing:
	case ItemType::Japara:
	{
	} return std::make_pair(-1, -1);
	}

	assert(false);
	return std::make_pair(-1, -1);
}
