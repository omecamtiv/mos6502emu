#include "ui.hpp"

#include <ncurses.h>

#include <cstring>

void UI::initui() {
	int c;
	char char_q = 'q';
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	init_base();
	while (c != char_q) {
		c = getch();
		switch (c) {
			case KEY_RESIZE:
				init_base();
				break;
			default:;
		}
	}
	endwin();
	return;
}

void UI::init_base() {
	int row, col, win_row, win_col, start_y, start_x;
	getmaxyx(stdscr, row, col);
	win_col = col - (col % 8);
	win_row = (win_col / 8) * 3;
	while (win_row > row || win_col > col) {
		win_row -= 8;
		win_col -= 3;
	}
	start_y = row / 2 - win_row / 2;
	start_x = col / 2 - win_col / 2;
	clear();
	base_win = newwin(win_row, win_col, start_y, start_x);
	refresh();
	box(base_win, 0, 0);
	init_status(status_win, base_win);
	init_cmd(cmd_win, base_win);
	return;
}

void UI::init_status(WINDOW *win, WINDOW *parent_win) {
	int row, col, win_row, win_col, start_y, start_x;
	getmaxyx(parent_win, row, col);
	win_row = 5;
	win_col = 26;
	start_y = 2;
	start_x = 1;
	win = derwin(parent_win, win_row, win_col, start_y, start_x);
	wrefresh(parent_win);
	box(win, 0, 0);
	wrefresh(win);
	return;
}

void UI::init_cmd(WINDOW *win, WINDOW *parent_win) {
	int row, col, win_row, win_col, start_y, start_x;
	getmaxyx(parent_win, row, col);
	win_row = 3;
	win_col = col - 2;
	start_y = row - 4;
	start_x = 1;
	win = derwin(parent_win, win_row, win_col, start_y, start_x);
	wrefresh(parent_win);
	box(win, 0, 0);
	wrefresh(win);
	return;
}

void UI::init_ram(WINDOW *win, WINDOW *parent_win) {
	int row, col, win_row, win_col, start_y, start_x;
	getmaxyx(win, row, col);
	win_row = 3;
	win_col = col - 2;
	start_y = row - 4;
	start_x = 1;
	win = derwin(parent_win, win_row, win_col, start_y, start_x);
	wrefresh(parent_win);
	box(parent_win, 0, 0);
	wrefresh(win);
	return;
}
