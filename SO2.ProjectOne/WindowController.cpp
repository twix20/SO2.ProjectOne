#include "stdafx.h"
#include "WindowController.h"


WindowController::WindowController(const int height, const int width)
{
	//Init ncurses
	initscr();
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

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

std::vector<MovingArea> WindowController::splitIntoAreas() const
{
	std::vector<MovingArea> result;

	const int sharedHeight = height / 2;
	const int sharedWidth = width / 2;

	result.push_back({ 0,            0,           sharedHeight, sharedWidth });
	result.push_back({ 0,            sharedHeight, sharedHeight, sharedWidth });
	result.push_back({ sharedWidth, 0,            sharedHeight, sharedWidth });
	result.push_back({ sharedWidth, sharedHeight,  sharedHeight, sharedWidth });

	drawHorizontalLine(1, height / 2, '_', width - 2);
	drawVerticalLine(width / 2, 1, '|', height - 2);

	const int offest = 1;
	for (auto& a : result)
	{
		a.topLeftX += offest;
		a.width -= offest + 1;

		a.topLeftY += offest;
		a.height -= offest + 1;
	}

	return result;
}

void WindowController::clearPosition(const int x, const int y) const
{
	std::lock_guard<std::mutex> lock(ncursesMx);

	mvwaddch(win.get(), y, x, ' ');
	wrefresh(win.get());
}

void WindowController::drawHorizontalLine(const int x, const int y, chtype ch, const int n) const
{
	std::lock_guard<std::mutex> lock(ncursesMx);

	mvwhline(win.get(), y, x, ch, n);
	wrefresh(win.get());
}

void WindowController::drawVerticalLine(const int x, const int y, const chtype ch, const int n) const
{
	std::lock_guard<std::mutex> lock(ncursesMx);

	mvwvline(win.get(), y, x, ch, n);
	wrefresh(win.get());
}

void WindowController::drawCharAtPosition(const int x, const int y, const char mark, int colorPair) const
{
	std::lock_guard<std::mutex> lock(this->ncursesMx);

	wattron(win.get(), COLOR_PAIR(colorPair));
	mvwaddch(win.get(), y, x, mark);
	wattroff(win.get(), COLOR_PAIR(colorPair));

	wrefresh(win.get());
}

void WindowController::drawChunk(SnakeChunk& chunk) const
{
	drawCharAtPosition(chunk.x, chunk.y, chunk.mark, chunk.colorPair);
}


