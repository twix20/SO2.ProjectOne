#include "stdafx.h"
#include "WindowController.h"


WindowController::WindowController(int height, int width)
{
	//Init ncurses
	initscr();

	this->height = height;
	this->width = width;

	win = std::shared_ptr<WINDOW>(newwin(height, width, 1, 1));

	refresh();
	//Create box border
	box(win.get(), 0, 0);
		
}

WindowController::~WindowController()
{
	//Dispose ncurses
	endwin();
}

void WindowController::clearPosition(const int x, const int y) const
{
	std::lock_guard<std::mutex> lock(this->ncursesMx);

	mvwaddch(win.get(), y, x, ' ');
	wrefresh(win.get());
}

void WindowController::drawCharAtPosition(const int x, const int y, const char mark) const
{
	std::lock_guard<std::mutex> lock(this->ncursesMx);

	mvwaddch(win.get(), y, x, mark);
	wrefresh(win.get());
}