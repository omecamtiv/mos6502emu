#include "ui.hpp"

#include <ncurses.h>

#include <cstring>

void UI::initui() {
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	init_base(base_win, stdscr);

	getch();
	endwin();
	return;
}

void UI::init_base(WINDOW *win, WINDOW *parent_win) {
	int row, col, start_y, start_x;
	const int ROW = 40;
	const int COL = 140;
	getmaxyx(parent_win, row, col);
	start_y = row / 2 - ROW / 2;
	start_x = col / 2 - COL / 2;
	win = newwin(ROW, COL, start_y, start_x);
	refresh();
	box(win, 0, 0);
	const char BASE_HEADING[] = "MOS-6502  EMULATOR";
	int len = strlen(BASE_HEADING);
	int pos_x = COL / 2 - len / 2;
	int pos_y = 1;
	mvwprintw(win, pos_y, pos_x, BASE_HEADING);
	wrefresh(win);
	return;
}
