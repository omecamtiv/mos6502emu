#ifndef UI_HPP
#define UI_HPP

#include <ncurses.h>

class UI {
       public:
	void create_win(WINDOW* win, int row, int col, int posy, int posx,
			const char* label);
};

#endif
