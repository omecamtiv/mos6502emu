#include <curses.h>
#include <ncurses.h>

#include "ui.hpp"
#define MEM_ROW 12
#define MEM_COL 34

void start_ui(WINDOW *win);

int main() {
	int c;
	char char_q = 'q';
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	start_ui(stdscr);
	while (c != char_q) {
		c = getch();
		switch (c) {
			case KEY_RESIZE:
				start_ui(stdscr);
				break;
			default:;
		}
	}
	endwin();
	return 0;
}

void start_ui(WINDOW *win) {
	WINDOW *zp_win, *stack_win;
	int row, col;
	start_color();
	init_pair(2, COLOR_BLACK, COLOR_RED);
	const char zp_label[] = "ZERO  PAGE";
	const char stack_label[] = "STACK MEMORY";
	getmaxyx(win, row, col);
	UI().create_win(zp_win, MEM_ROW, MEM_COL, 0, col - MEM_COL, zp_label);
	UI().create_win(stack_win, MEM_ROW, MEM_COL, MEM_ROW, col - MEM_COL,
			stack_label);
	wattron(win, COLOR_PAIR(2));
	mvwhline(win, row - 3, 0, ACS_HLINE, col);
	wattroff(win, COLOR_PAIR(2));
	wrefresh(win);
	return;
}
