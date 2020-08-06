//  ===== Date Created: 15 July, 2020 ===== 

#if !defined(COMMON_HPP)
#define COMMON_HPP

/*
 * Dimensions of the window
 */
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

/*
 * Dimensions of some buttons drawn to the screen.
 */
#define HOME_PAGE_BUTTON_WIDTH WINDOW_WIDTH * 20 / 100
#define HOME_PAGE_BUTTON_HEIGHT WINDOW_HEIGHT * 10 / 100
#define MANAGE_PAGE_BUTTON_WIDTH WINDOW_WIDTH * 20 / 100
#define MANAGE_PAGE_BUTTON_HEIGHT WINDOW_HEIGHT * 10 / 100

/*
 * Sets the object's origin to the center of it.
 *
 * Input: Must be a valid sf::Transformable object
 */
#define SET_ORIGIN_CENTER(obj) obj.setOrigin(obj.getGlobalBounds().left + (obj.getGlobalBounds().width / 2), obj.getGlobalBounds().top + (obj.getGlobalBounds().height / 2))

/*
 * Values for ease of drawing the databases
 */
constexpr unsigned int tableX = WINDOW_WIDTH * 5 / 100;
constexpr unsigned int tableY = WINDOW_HEIGHT * 22 / 100;
constexpr unsigned int tableWidth = WINDOW_WIDTH * 90 / 100;
constexpr unsigned int tableHeight = WINDOW_HEIGHT * 75 / 100;

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

#endif
