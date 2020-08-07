//  ===== Date Created: 17 July, 2020 ===== 

#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <functional>

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
	initAddRemoveCadetPages();
	initBackupPages();
	initGetSizesPage();
	initUniformHandlingPages();

	backButton = new Button(font, "<--",
							sf::Vector2i { WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 5 / 100},
							sf::Vector2i { WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 3 / 100});

	searchTextbox = new TextBox(font,
								sf::Vector2i { WINDOW_WIDTH * 85 / 100, WINDOW_HEIGHT * 18 / 100 },
								sf::Vector2i { WINDOW_WIDTH * 18 / 100, WINDOW_HEIGHT * 5 / 100 });
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

		case ProgramState::IssuesPage:
		{
			issueButton->handleMouseMove(mousePos);
			handlingTypeMenu->handleMouseMove(mousePos);
		} break;
		
		case ProgramState::ExchangesPage:
		{
			exchangeButton->handleMouseMove(mousePos);
			handlingTypeMenu->handleMouseMove(mousePos);
		} break;
		
		case ProgramState::ReturnsPage:
		{
			returnButton->handleMouseMove(mousePos);
			handlingTypeMenu->handleMouseMove(mousePos);
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
			addItemButton->handleMouseMove(mousePos);
		} break;

		case ProgramState::RemoveItemPage:
		{
			typeSelectionMenu->handleMouseMove(mousePos);
			removeItemButton->handleMouseMove(mousePos);
		} break;

		case ProgramState::AddCadetPage:
		{
			addCadetButton->handleMouseMove(mousePos);
		} break;

		case ProgramState::RemoveCadetPage:
		{
			removeCadetButton->handleMouseMove(mousePos);
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

		case ProgramState::IssuesPage:
		{
			issueButton->handleMouseDown(mousePos);
			handlingTypeMenu->handleMouseDown(mousePos);
		} break;
				
		case ProgramState::ExchangesPage:
		{
			exchangeButton->handleMouseDown(mousePos);
			handlingTypeMenu->handleMouseDown(mousePos);
		} break;
				
		case ProgramState::ReturnsPage:
		{
			returnButton->handleMouseDown(mousePos);
			handlingTypeMenu->handleMouseDown(mousePos);
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
			addItemButton->handleMouseDown(mousePos);
		} break;

		case ProgramState::RemoveItemPage:
		{
			typeSelectionMenu->handleMouseDown(mousePos);
			removeItemButton->handleMouseDown(mousePos);
		} break;
		
		case ProgramState::AddCadetPage:
		{
			addCadetButton->handleMouseDown(mousePos);
		} break;

		case ProgramState::RemoveCadetPage:
		{
			removeCadetButton->handleMouseDown(mousePos);
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

		case ProgramState::ViewDatabasePage:
		{
			if (mousePos.x >= typeX && mousePos.x <= typeX + typeWidth)
			{
				sortItemsDatabase(ItemField::Type);
			}
			else if (mousePos.x >= sizeX && mousePos.x <= sizeX + sizeWidth)
			{
				sortItemsDatabase(ItemField::Size);
			}
			else if (mousePos.x >= quantityX && mousePos.x <= quantityX + quantityWidth)
			{
				sortItemsDatabase(ItemField::Quantity);
			}
			else if (mousePos.x >= quantityOnOrderX && mousePos.x <= quantityOnOrderX + quantityOnOrderWidth)
			{
				sortItemsDatabase(ItemField::QuantityOnOrder);
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
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		
		switch (programState)
		{
		case ProgramState::HomePage:
		{
			for (unsigned int i = 0; i < HOME_PAGE_BUTTON_COUNT; i++)
			{
				if (homePageButtons[i].handleMouseUp())
				{
					lastProgramState = ProgramState::HomePage;
					
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

		case ProgramState::IssuesPage:
		{
			handlingTypeMenu->handleMouseUp();
			handlingServiceNumberTextbox->handleMouseUp(mousePos);
			handlingNameTextbox->handleMouseUp(mousePos);
			handlingSizeInTextbox->handleMouseUp(mousePos);
			handlingQuantityInTextbox->handleMouseUp(mousePos);

			if (issueButton->handleMouseUp())
			{
				// TODO(fkp): Issue
			}
		} break;

		case ProgramState::ExchangesPage:
		{
			handlingTypeMenu->handleMouseUp();
			handlingServiceNumberTextbox->handleMouseUp(mousePos);
			handlingNameTextbox->handleMouseUp(mousePos);
			handlingSizeInTextbox->handleMouseUp(mousePos);
			handlingQuantityInTextbox->handleMouseUp(mousePos);
			handlingSizeOutTextbox->handleMouseUp(mousePos);
			handlingQuantityOutTextbox->handleMouseUp(mousePos);

			if (exchangeButton->handleMouseUp())
			{
				// TODO(fkp): Exchange
			}
		} break;

		case ProgramState::ReturnsPage:
		{
			handlingTypeMenu->handleMouseUp();
			handlingServiceNumberTextbox->handleMouseUp(mousePos);
			handlingNameTextbox->handleMouseUp(mousePos);
			handlingSizeInTextbox->handleMouseUp(mousePos);
			handlingQuantityInTextbox->handleMouseUp(mousePos);

			if (returnButton->handleMouseUp())
			{
				// TODO(fkp): Return
			}
		} break;

		case ProgramState::ManagePage:
		{
			for (int i = 0; i < managePageButtons.size(); i++)
			{
				Button& button = managePageButtons[i];
				
				if (button.handleMouseUp())
				{
					lastProgramState = ProgramState::ManagePage;
					
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

					case ADD_CADET_BUTTON:
					{
						programState = ProgramState::AddCadetPage;
					} break;

					case REMOVE_CADET_BUTTON:
					{
						programState = ProgramState::RemoveCadetPage;
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
					lastProgramState = ProgramState::HomePage;
					programState = ProgramState::ManagePage;
				}
				else
				{
					MessageBox(nullptr, "Your username or password is incorrect.", nullptr, MB_OK);
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

				programState = lastProgramState;
				lastProgramState = ProgramState::HomePage;
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
				
				programState = lastProgramState;
				lastProgramState = ProgramState::HomePage;
			}
		} break;

		case ProgramState::AddItemPage:
		case ProgramState::RemoveItemPage:
		{
			typeSelectionMenu->handleMouseUp();

			if ((programState == ProgramState::AddItemPage && addItemButton->handleMouseUp()) ||
				(programState == ProgramState::RemoveItemPage && removeItemButton->handleMouseUp()))
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

		case ProgramState::AddCadetPage:
		{
			if (addCadetButton->handleMouseUp())
			{
				if (serviceNumberTextbox->getText() != "" &&
					rankTextbox->getText() != "" &&
					nameTextbox->getText() != "")
				{
					Cadet newCadet;
					newCadet.serviceNumber = std::stoi(serviceNumberTextbox->getText());
					newCadet.rankAbbrev = rankTextbox->getText();
					const std::string& fullName = nameTextbox->getText();
					newCadet.firstName = fullName.substr(0, fullName.find_last_of(" "));
					newCadet.lastName = fullName.substr(fullName.find_last_of(" ") + 1);

					cadetDatabaseShown.emplace_back(newCadet);
					cadetDatabase.emplace_back(std::move(newCadet));
					
					serviceNumberTextbox->reset();
					rankTextbox->reset();
					nameTextbox->reset();
				}
				else
				{
					MessageBox(nullptr, "Please fill all details.", nullptr, MB_OK);
				}
			}
			
			serviceNumberTextbox->handleMouseUp(mousePos);
			rankTextbox->handleMouseUp(mousePos);
			nameTextbox->handleMouseUp(mousePos);
		} break;

		case ProgramState::RemoveCadetPage:
		{
			if (removeCadetButton->handleMouseUp())
			{
				bool shouldReset = false;
				
				if (serviceNumberTextbox->getText() != "")
				{
					for (int i = 0; i < cadetDatabase.size();)
					{
						Cadet& cadet = cadetDatabase[i];
						
						if ((int) cadet.serviceNumber == std::stoi(serviceNumberTextbox->getText()))
						{
							cadetDatabase.erase(cadetDatabase.begin() + i);
							shouldReset = true;
						}
						else
						{
							i += 1;
						}
					}
				}
				
				if (nameTextbox->getText() != "")
				{
					for (int i = 0; i < cadetDatabase.size();)
					{
						Cadet& cadet = cadetDatabase[i];
						
						if (cadet.firstName + " " + cadet.lastName == nameTextbox->getText())
						{
							cadetDatabase.erase(cadetDatabase.begin() + i);
							shouldReset = true;
						}
						else
						{
							i += 1;
						}
					}
				}

				if (shouldReset)
				{
					serviceNumberTextbox->reset();
					rankTextbox->reset();
					nameTextbox->reset();
				}
				else
				{
					MessageBox(nullptr, "No cadet found.", nullptr, MB_OK);
				}
			}
			
			serviceNumberTextbox->handleMouseUp(mousePos);
			rankTextbox->handleMouseUp(mousePos);
			nameTextbox->handleMouseUp(mousePos);

			cadetDatabaseShown = cadetDatabase;
		} break;
			
		case ProgramState::GetSizesPage:
		{
			for (TextBox& textbox : getSizesPageTextboxes)
			{
				textbox.handleMouseUp(mousePos);
			}

			if (calculateSizesButton->handleMouseUp())
			{
				bool filledInCompletely = true;
				
				for (TextBox& textbox : getSizesPageTextboxes)
				{
					if (textbox.getText() == "")
					{
						filledInCompletely = false;
						MessageBox(nullptr, "Please fill in all the values.", nullptr, MB_OK);
						
						break;
					}
				}

				if (filledInCompletely)
				{
					// For ease of use
					std::vector<TextBox>& textboxes = getSizesPageTextboxes;
					
					std::string lssdShirtSize = textboxes[NECK_SIZE_INDEX].getText() + "/" + textboxes[SLEEVE_SIZE_INDEX].getText();
					std::string sssdShirtSize = textboxes[NECK_SIZE_INDEX].getText();

					std::string dpuShirtSize = textboxes[CHEST_SIZE_INDEX].getText();
					std::string dpuPantsSize = textboxes[WAIST_SIZE_INDEX].getText();
					
					// TODO(fkp): Proper SD Trousers subsize (S, R, L)
					std::string sdTrousersSize = std::to_string(roundUp(std::stoi(textboxes[WAIST_SIZE_INDEX].getText()), 5)) + "R";

					std::string jumperSize;
					int jumperMeasurement = std::stoi(textboxes[CHEST_SIZE_INDEX].getText());

					if (jumperMeasurement <= 85)
					{
						jumperSize = "75-85";
					}
					else if (jumperMeasurement <= 95)
					{
						jumperSize = "85-95";
					}
					else if (jumperMeasurement <= 105)
					{
						jumperSize = "95-105";
					}
					else if (jumperMeasurement <= 115)
					{
						jumperSize = "105-115";
					}
					else if (jumperMeasurement <= 125)
					{
						jumperSize = "115-125";
					}
					else
					{
						MessageBox(nullptr, "Jumper size does not exist.", nullptr, MB_OK);
					}

					std::string shoeSize = textboxes[SHOE_SIZE_INDEX].getText();
					std::string hffkSize = textboxes[HEAD_SIZE_INDEX].getText();
					std::string puggareeSize = hffkSize;

					int headMeasurement = std::stoi(textboxes[HEAD_SIZE_INDEX].getText());
					std::string bushHatSize;

					if (headMeasurement >= 58)
					{
						bushHatSize = "Large";
					}
					else if (headMeasurement >= 54)
					{
						bushHatSize = "Medium";
					}
					else
					{
						bushHatSize = "Small";
					}

					viewSizesPageTexts[0].setString(std::string("LSSD Shirt Size: ") + lssdShirtSize);
					viewSizesPageTexts[1].setString(std::string("SSSD Shirt Size: ") + sssdShirtSize);
					viewSizesPageTexts[2].setString(std::string("SD Trousers Size: ") + sdTrousersSize);
					viewSizesPageTexts[3].setString(std::string("DPU Shirt Size: ") + dpuShirtSize);
					viewSizesPageTexts[4].setString(std::string("DPU Pants Size: ") + dpuPantsSize);
					viewSizesPageTexts[5].setString(std::string("Jumper Size: ") + jumperSize);
					viewSizesPageTexts[6].setString(std::string("HFFK Size: ") + hffkSize);
					viewSizesPageTexts[7].setString(std::string("Puggaree Size: ") + puggareeSize);
					viewSizesPageTexts[8].setString(std::string("Bush Hat Size: ") + bushHatSize);
					viewSizesPageTexts[9].setString(std::string("Shoe Size: ") + shoeSize);

					programState = ProgramState::ViewSizesPage;
					lastProgramState = ProgramState::ManagePage;
				}
			}
		} break;

		case ProgramState::ViewDatabasePage:
		{
			if (cadetDatabaseIsActive)
			{
				searchTextbox->handleMouseUp(mousePos);
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
				programState = lastProgramState;
				lastProgramState = ProgramState::HomePage;
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

		case ProgramState::IssuesPage:
		{
			handlingServiceNumberTextbox->handleTextInput(event);
			handlingNameTextbox->handleTextInput(event);
			handlingSizeInTextbox->handleTextInput(event);
			handlingQuantityInTextbox->handleTextInput(event);
		} break;

		case ProgramState::ExchangesPage:
		{
			handlingServiceNumberTextbox->handleTextInput(event);
			handlingNameTextbox->handleTextInput(event);
			handlingSizeInTextbox->handleTextInput(event);
			handlingQuantityInTextbox->handleTextInput(event);
			handlingSizeOutTextbox->handleTextInput(event);
			handlingQuantityOutTextbox->handleTextInput(event);
		} break;

		case ProgramState::ReturnsPage:
		{
			handlingServiceNumberTextbox->handleTextInput(event);
			handlingNameTextbox->handleTextInput(event);
			handlingSizeInTextbox->handleTextInput(event);
			handlingQuantityInTextbox->handleTextInput(event);
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

		case ProgramState::AddCadetPage:
		case ProgramState::RemoveCadetPage:
		{
			serviceNumberTextbox->handleTextInput(event);
			rankTextbox->handleTextInput(event);
			nameTextbox->handleTextInput(event);
		} break;

		case ProgramState::GetSizesPage:
		{
			for (TextBox& textbox : getSizesPageTextboxes)
			{
				textbox.handleTextInput(event);
			}
		} break;

		case ProgramState::ViewDatabasePage:
		{
			if (cadetDatabaseIsActive)
			{
				searchTextbox->handleTextInput(event);
				cadetDatabaseShown.clear();
				const std::string& query = searchTextbox->getText();

				for (Cadet& cadet : cadetDatabase)
				{
					if (cadet.lastName.find(query) != std::string::npos ||
						cadet.firstName.find(query) != std::string::npos)
					{
						cadetDatabaseShown.emplace_back(cadet);
					}
				}
			}
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
		
		sf::RectangleShape background { sf::Vector2f { tableWidth, tableHeight } };
		background.setPosition(tableX, tableY);
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
		issueButton->draw(target);
		
		target.draw(handlingServiceNumberText);
		handlingServiceNumberTextbox->draw(target);
		target.draw(handlingNameText);
		handlingNameTextbox->draw(target);
		target.draw(handlingSizeText);
		handlingSizeInTextbox->draw(target);
		target.draw(handlingQuantityText);
		handlingQuantityInTextbox->draw(target);
		handlingTypeMenu->draw(target);
	} break;

	case ProgramState::ExchangesPage:
	{
		target.draw(titleText);
		exchangeButton->draw(target);

		target.draw(handlingServiceNumberText);
		handlingServiceNumberTextbox->draw(target);
		target.draw(handlingNameText);
		handlingNameTextbox->draw(target);
		target.draw(handlingSizeInText);
		handlingSizeInTextbox->draw(target);
		target.draw(handlingQuantityInText);
		handlingQuantityInTextbox->draw(target);
		target.draw(handlingSizeOutText);
		handlingSizeOutTextbox->draw(target);
		target.draw(handlingQuantityOutText);
		handlingQuantityOutTextbox->draw(target);
		handlingTypeMenu->draw(target);
	} break;

	case ProgramState::ReturnsPage:
	{
		target.draw(titleText);
		returnButton->draw(target);

		target.draw(handlingServiceNumberText);
		handlingServiceNumberTextbox->draw(target);
		target.draw(handlingNameText);
		handlingNameTextbox->draw(target);
		target.draw(handlingSizeText);
		handlingSizeInTextbox->draw(target);
		target.draw(handlingQuantityText);
		handlingQuantityInTextbox->draw(target);
		handlingTypeMenu->draw(target);
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
			addItemButton->draw(target);
		}
		else if (programState == ProgramState::RemoveItemPage)
		{
			removeItemButton->draw(target);
		}
		
		typeSelectionMenu->draw(target);

		target.draw(sizeText);
		target.draw(quantityText);
		target.draw(quantityOrderedText);
		
		sizeTextbox->draw(target);
		quantityTextbox->draw(target);
		quantityOrderedTextbox->draw(target);
	} break;
	
	case ProgramState::AddCadetPage:
	case ProgramState::RemoveCadetPage:
	{
		if (programState == ProgramState::AddCadetPage)
		{
			addCadetButton->draw(target);
		}
		else if (programState == ProgramState::RemoveCadetPage)
		{
			removeCadetButton->draw(target);
		}
		
		target.draw(serviceNumberText);
		target.draw(rankText);
		target.draw(nameText);
		
		serviceNumberTextbox->draw(target);
		rankTextbox->draw(target);
		nameTextbox->draw(target);
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

	case ProgramState::ViewSizesPage:
	{
		for (sf::Text& text : viewSizesPageTexts)
		{
			target.draw(text);
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
	addItemButton = new Button(font, "Add",
						   sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 60 / 100 },
						   sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });
	
	removeItemButton = new Button(font, "Remove",
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

void CLogButBetter::initAddRemoveCadetPages()
{
	addCadetButton = new Button(font, "Add",
								sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 60 / 100 },
								sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });
	
	removeCadetButton = new Button(font, "Remove",
								   sf::Vector2i { WINDOW_WIDTH * 50 / 100, WINDOW_HEIGHT * 60 / 100 },
								   sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });
		
	serviceNumberText = sf::Text { "Service Number:", font, 24 };
	serviceNumberText.setFillColor(sf::Color::Black);
	serviceNumberText.setPosition((WINDOW_WIDTH * 20 / 100) - (serviceNumberText.getGlobalBounds().width / 2),
								  (WINDOW_HEIGHT * 25 / 100) - (serviceNumberText.getGlobalBounds().height / 2));
	
	rankText = sf::Text { "Rank:", font, 24 };
	rankText.setFillColor(sf::Color::Black);
	rankText.setPosition((WINDOW_WIDTH * 40 / 100) - (rankText.getGlobalBounds().width / 2),
						 (WINDOW_HEIGHT * 25 / 100) - (rankText.getGlobalBounds().height / 2));
	
	nameText = sf::Text { "Name:", font, 24 };
	nameText.setFillColor(sf::Color::Black);
	nameText.setPosition((WINDOW_WIDTH * 70 / 100) - (nameText.getGlobalBounds().width / 2),
						 (WINDOW_HEIGHT * 25 / 100) - (nameText.getGlobalBounds().height / 2));
	
	serviceNumberTextbox = new TextBox(font,
									   sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 35 / 100 },
									   sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 5 / 100 });
	serviceNumberTextbox->setNumbersOnly(true);
	serviceNumberTextbox->setActive(true);
	
	rankTextbox = new TextBox(font,
							  sf::Vector2i { WINDOW_WIDTH * 40 / 100, WINDOW_HEIGHT * 35 / 100 },
							  sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 5 / 100 });
	
	nameTextbox = new TextBox(font,
							  sf::Vector2i { WINDOW_WIDTH * 70 / 100, WINDOW_HEIGHT * 35 / 100 },
							  sf::Vector2i { WINDOW_WIDTH * 35 / 100, WINDOW_HEIGHT * 5 / 100 });
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

	// NOTE(fkp): Magic number 10 represents number of items
	for (int i = 0; i < 10; i++)
	{
		viewSizesPageTexts.emplace_back("", font, 24);
		viewSizesPageTexts.back().setFillColor(sf::Color::Black);
		SET_ORIGIN_CENTER(viewSizesPageTexts.back());
		viewSizesPageTexts.back().setPosition((float) (WINDOW_WIDTH * 40 / 100), (float) (WINDOW_HEIGHT * 25 / 100) + (WINDOW_HEIGHT * 5 / 100 * i));
	}
}

void CLogButBetter::initUniformHandlingPages()
{
	handlingServiceNumberText = sf::Text { "Service #:", font, 24 };
	handlingServiceNumberText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(handlingServiceNumberText);
	handlingServiceNumberText.setPosition(WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 35 / 100);

	handlingServiceNumberTextbox = new TextBox(font,
											   sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 40 / 100 },
											   sf::Vector2i { WINDOW_WIDTH * 13 / 100, WINDOW_HEIGHT * 5 / 100 });
	handlingServiceNumberTextbox->setNumbersOnly(true);
	
	handlingNameText = sf::Text { "Name:", font, 24 };
	handlingNameText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(handlingNameText);
	handlingNameText.setPosition(WINDOW_WIDTH * 30 / 100, WINDOW_HEIGHT * 35 / 100);
	
	handlingNameTextbox = new TextBox(font,
									  sf::Vector2i { WINDOW_WIDTH * 30 / 100, WINDOW_HEIGHT * 40 / 100 },
									  sf::Vector2i { WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 5 / 100 });
	
	handlingTypeMenu = new DropDownMenu(font, "Type?", { "LSSD Shirt", "SSSD Shirt",
													  "SD Trousers", "SD Jumper",
													  "SD Belt", "SD Shoes",
													  "DPU Shirt", "DPU Pants",
													  "DPU Jumper", "DPU Boots",
													  "HFFK", "Hat Badge",
													  "Puggaree", "Bush Hat",
													  "Rank Slides", "Webbing",
													  "Japara" },
		sf::Vector2i { WINDOW_WIDTH * 57 / 100, WINDOW_HEIGHT * 20 / 100 });
	
	handlingSizeText = sf::Text { "Size:", font, 24 };
	handlingSizeText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(handlingSizeText);
	handlingSizeText.setPosition(WINDOW_WIDTH * 75 / 100, WINDOW_HEIGHT * 35 / 100);
	
	handlingQuantityText = sf::Text { "Quantity:", font, 24 };
	handlingQuantityText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(handlingQuantityText);
	handlingQuantityText.setPosition(WINDOW_WIDTH * 90 / 100, WINDOW_HEIGHT * 35 / 100);
	
	handlingSizeInText = sf::Text { "Size In:", font, 24 };
	handlingSizeInText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(handlingSizeInText);
	handlingSizeInText.setPosition(WINDOW_WIDTH * 75 / 100, WINDOW_HEIGHT * 35 / 100);
	
	handlingSizeInTextbox = new TextBox(font,
								   sf::Vector2i { WINDOW_WIDTH * 75 / 100, WINDOW_HEIGHT * 40 / 100 },
								   sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 5 / 100 });

	handlingQuantityInText = sf::Text { "Quantity In:", font, 24 };
	handlingQuantityInText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(handlingQuantityInText);
	handlingQuantityInText.setPosition(WINDOW_WIDTH * 90 / 100, WINDOW_HEIGHT * 35 / 100);
	
	handlingQuantityInTextbox = new TextBox(font,
								   sf::Vector2i { WINDOW_WIDTH * 90 / 100, WINDOW_HEIGHT * 40 / 100 },
								   sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 5 / 100 });
	handlingQuantityInTextbox->setNumbersOnly(true);

	handlingSizeOutText = sf::Text { "Size Out:", font, 24 };
	handlingSizeOutText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(handlingSizeOutText);
	handlingSizeOutText.setPosition(WINDOW_WIDTH * 75 / 100, WINDOW_HEIGHT * 50 / 100);
	
	handlingSizeOutTextbox = new TextBox(font,
								   sf::Vector2i { WINDOW_WIDTH * 75 / 100, WINDOW_HEIGHT * 55 / 100 },
								   sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 5 / 100 });

	handlingQuantityOutText = sf::Text { "Quantity Out:", font, 24 };
	handlingQuantityOutText.setFillColor(sf::Color::Black);
	SET_ORIGIN_CENTER(handlingQuantityOutText);
	handlingQuantityOutText.setPosition(WINDOW_WIDTH * 90 / 100, WINDOW_HEIGHT * 50 / 100);
	
	handlingQuantityOutTextbox = new TextBox(font,
								   sf::Vector2i { WINDOW_WIDTH * 90 / 100, WINDOW_HEIGHT * 55 / 100 },
								   sf::Vector2i { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 5 / 100 });
	handlingQuantityOutTextbox->setNumbersOnly(true);

	issueButton = new Button(font, "Issue",
							 sf::Vector2i { WINDOW_WIDTH * 35 / 100, WINDOW_HEIGHT * 75 / 100 },
							 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });
	
	exchangeButton = new Button(font, "Exchange",
							 sf::Vector2i { WINDOW_WIDTH * 35 / 100, WINDOW_HEIGHT * 75 / 100 },
							 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });
	returnButton = new Button(font, "Return",
							 sf::Vector2i { WINDOW_WIDTH * 35 / 100, WINDOW_HEIGHT * 75 / 100 },
							 sf::Vector2i { WINDOW_WIDTH * 20 / 100, WINDOW_HEIGHT * 10 / 100 });
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
	
	constexpr unsigned int shirtsX = nameX + nameWidth + 5;
	constexpr unsigned int shirtsWidth = tableWidth * 10 / 100;
	constexpr unsigned int pantsX = shirtsX + shirtsWidth + 5;
	constexpr unsigned int pantsWidth = tableWidth * 10 / 100;
	constexpr unsigned int shoesX = pantsX + pantsWidth + 5;
	constexpr unsigned int shoesWidth = tableWidth * 10 / 100;
	constexpr unsigned int hatsX = shoesX + shoesWidth + 5;
	constexpr unsigned int hatsWidth = tableWidth * 10 / 100;
	
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

	entryText.setString("Shirts");
	entryText.setPosition((float) shirtsX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Pants");
	entryText.setPosition((float) pantsX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Shoes");
	entryText.setPosition((float) shoesX, (float) currentY);
	target.draw(entryText);

	entryText.setString("Hats");
	entryText.setPosition((float) hatsX, (float) currentY);
	target.draw(entryText);

	currentY += entryText.getCharacterSize() + 3;
	entryText.setStyle(sf::Text::Regular);
		
	for (Cadet& cadet : cadetDatabaseShown)
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

		unsigned int numberOfShirts = 0;
		unsigned int numberOfPants = 0;
		unsigned int numberOfShoes = 0;
		unsigned int numberOfHats = 0;

		for (ItemGroup& item : cadet.items)
		{
			switch (item.type)
			{
			case ItemType::SD_LongSleeve:
			case ItemType::SD_ShortSleeve:
			case ItemType::DPU_Shirt:
				numberOfShirts += item.quantity;
				break;
				
			case ItemType::SD_Trousers:
			case ItemType::DPU_Pants:
				numberOfPants += item.quantity;
				break;
				
			case ItemType::SD_Shoes:
			case ItemType::DPU_Boots:
				numberOfShoes += item.quantity;
				break;
				
			case ItemType::Hat_HFFK:
			case ItemType::Hat_Bush:
				numberOfHats += item.quantity;
				break;
			}
		}

		entryText.setString(std::to_string(numberOfShirts));
		entryText.setPosition((float) shirtsX, (float) currentY);
		target.draw(entryText);

		entryText.setString(std::to_string(numberOfPants));
		entryText.setPosition((float) pantsX, (float) currentY);
		target.draw(entryText);

		entryText.setString(std::to_string(numberOfShoes));
		entryText.setPosition((float) shoesX, (float) currentY);
		target.draw(entryText);

		entryText.setString(std::to_string(numberOfHats));
		entryText.setPosition((float) hatsX, (float) currentY);
		target.draw(entryText);

		currentY += entryText.getCharacterSize() + 2;
	}

	// Draws the grid
	verticalLine.setPosition(rankX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(nameX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(shirtsX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(pantsX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(shoesX - 5, tableY);
	target.draw(verticalLine);
	verticalLine.setPosition(hatsX - 5, tableY);
	target.draw(verticalLine);

	// NOTE(fkp): +3 skips the header row, +2 for each row after
	for (int y = tableY + entryText.getCharacterSize() + 3; y < tableY + tableHeight; y += entryText.getCharacterSize() + 2)
	{
		horizontalLine.setPosition(tableX, (float) y);
		target.draw(horizontalLine);			
	}

	// Draws the search box
	searchTextbox->draw(target);
}

void CLogButBetter::drawItemDatabase(sf::RenderTarget& target, sf::RectangleShape& horizontalLine, sf::RectangleShape& verticalLine)
{
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
	for (int y = tableY + entryText.getCharacterSize() + 3; y < tableY + tableHeight; y += entryText.getCharacterSize() + 2)
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

std::ostream& operator<<(std::ostream& stream, const ItemGroup& itemGroup)
{
	stream << getStringFromItemType(itemGroup.type) << ",";
	stream << itemGroup.size << ",";
	stream << itemGroup.subsize << ",";
	stream << itemGroup.quantity << ",";
	stream << itemGroup.quantityOnOrder << ",";
	stream << itemGroup.notes;

	return stream;
}

ItemGroup readItemFromStream(std::istream& line)
{
	ItemGroup result;

	std::string itemType;
	READ_STRING_UNTIL_COMMA(itemType);
	result.type = getItemTypeFromString(itemType);

	int itemSize;
	READ_INT_UNTIL_COMMA(itemSize, itemSizeStr);
	result.size = itemSize;

	int itemSubsize;
	READ_INT_UNTIL_COMMA(itemSubsize, itemSubsizeStr);
	result.subsize = itemSubsize;

	unsigned int itemQuantity;
	READ_UINT_UNTIL_COMMA(itemQuantity, itemQuantityStr);
	result.quantity = itemQuantity;

	unsigned int itemQuantityOnOrder;
	READ_UINT_UNTIL_COMMA(itemQuantityOnOrder, itemQuantityOnOrderStr);
	result.quantityOnOrder = itemQuantityOnOrder;

	std::string itemNotes;
	READ_STRING_UNTIL_COMMA(itemNotes);
	result.notes = itemNotes;

	return result;
}

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

		while (line && line.peek() != EOF)
		{
			cadetDatabase.back().items.emplace_back(readItemFromStream(line));
		}
	}

	cadetDatabaseShown = cadetDatabase;
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

		for (ItemGroup& item : cadet.items)
		{
			file << item << ",";
		}
		
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
		itemDatabase.emplace_back(std::move(readItemFromStream(line)));
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
		file << item << ",";
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

void CLogButBetter::sortItemsDatabase(ItemField field)
{
	std::function<bool(ItemGroup, ItemGroup)> sortFunction;
	
	switch (field)
	{
	case ItemField::Type:
	{
		sortFunction = [](ItemGroup first, ItemGroup second) { return (int) first.type < (int) second.type; };
	} break;

	case ItemField::Size:
	{
		sortFunction = [](ItemGroup first, ItemGroup second) { return first.size < (int) second.size; };
	} break;

	case ItemField::Quantity:
	{
		sortFunction = [](ItemGroup first, ItemGroup second) { return first.quantity < second.quantity; };
	} break;

	case ItemField::QuantityOnOrder:
	{
		sortFunction = [](ItemGroup first, ItemGroup second) { return first.quantityOnOrder < second.quantityOnOrder; };
	} break;

	default:
	{
		assert(false);
	} break;
	}

	std::sort(itemDatabase.begin(), itemDatabase.end(), sortFunction);
}

