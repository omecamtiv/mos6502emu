#ifndef UI_HPP
#define UI_HPP

#include <ncurses.h>
#include <panel.h>

class UI {
       public:
	WINDOW *base_win, *status_win, *ram_win, *menu_win, *cmd_win;
	PANEL *base_panel, *status_panel, *ram_panel, *menu_panel, *cmd_panel;
	void initui();
	void init_base(WINDOW *win, WINDOW *parent_win);
	void init_status(WINDOW *win, WINDOW *parent_win);
	void init_ram(WINDOW *win, WINDOW *parent_win);
	void init_menu(WINDOW *win, WINDOW *parent_win);
	void init_cmd(WINDOW *win, WINDOW *parent_win);
};

#endif
