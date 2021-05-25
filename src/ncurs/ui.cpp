#include "ui.hpp"

#include <cstring>

void UI::create_win(WINDOW *win, int row, int col, int posy, int posx,
		    const char *label) {
	int label_len = strlen(label);
	int start_x = col / 2 - label_len / 2;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	win = newwin(row, col, posy, posx);
	refresh();
	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, col - 2);
	mvwaddch(win, 2, col - 1, ACS_RTEE);
	wattron(win, COLOR_PAIR(1));
	mvwaddstr(win, 1, start_x, label);
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
	return;
}
