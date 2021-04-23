#ifndef UI_HPP
#define UI_HPP

#include <ncurses.h>

class UI {
	void init_base();
	void init_status(WINDOW *win, WINDOW *parent_win);
	void init_cmd(WINDOW *win, WINDOW *parent_win);
	void init_ram(WINDOW *win, WINDOW *parent_win);
	void init_menu(WINDOW *win, WINDOW *parent_win);

       public:
	WINDOW *base_win, *status_win, *ram_win, *menu_win, *cmd_win;
	void initui();
};

#endif
