//  ===== Date Created: 15 July, 2020 ===== 

#if !defined(COMMON_HPP)
#define COMMON_HPP

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#define HOME_PAGE_BUTTON_WIDTH WINDOW_WIDTH * 20 / 100
#define HOME_PAGE_BUTTON_HEIGHT WINDOW_HEIGHT * 10 / 100
#define MANAGE_PAGE_BUTTON_WIDTH WINDOW_WIDTH * 20 / 100
#define MANAGE_PAGE_BUTTON_HEIGHT WINDOW_HEIGHT * 10 / 100

#define SET_ORIGIN_CENTER(obj) obj.setOrigin(obj.getGlobalBounds().left + (obj.getGlobalBounds().width / 2), obj.getGlobalBounds().top + (obj.getGlobalBounds().height / 2))

// Values for ease of drawing the databases
constexpr unsigned int tableX = WINDOW_WIDTH * 5 / 100;
constexpr unsigned int tableY = WINDOW_HEIGHT * 20 / 100;
constexpr unsigned int tableWidth = WINDOW_WIDTH * 90 / 100;
constexpr unsigned int tableHeight = WINDOW_HEIGHT * 75 / 100;

#endif
