#include "stdafx.h"
#include "SecondWindowController.h"

SecondWindowController::SecondWindowController(const int height, const int width)
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

SecondWindowController::~SecondWindowController()
{
	//Dispose ncurses
	endwin();
}

std::vector<WallArea> SecondWindowController::splitIntoAreas() const
{
	std::vector<WallArea> result;

	const int sharedHeight = height / 2;
	const int sharedWidth = width / 2;

	result.push_back({ 0,            0,           sharedHeight, sharedWidth });
	result.push_back({ 0,            sharedHeight, sharedHeight, sharedWidth });
	result.push_back({ sharedWidth, 0,            sharedHeight, sharedWidth });
	result.push_back({ sharedWidth, sharedHeight,  sharedHeight, sharedWidth });

	drawHorizontalLine(1, height / 2, '-', width - 2);
	drawVerticalLine(width / 2, 1, '|', height - 2);

	return result;
}

void SecondWindowController::clearPosition(const int x, const int y) const
{
	std::lock_guard<std::mutex> lock(ncursesMx);

	mvwaddch(win.get(), y, x, ' ');
	wrefresh(win.get());
}

void SecondWindowController::drawHorizontalLine(const int x, const int y, chtype ch, const int n) const
{
	std::lock_guard<std::mutex> lock(ncursesMx);

	mvwhline(win.get(), y, x, ch, n);
	wrefresh(win.get());
}

void SecondWindowController::drawVerticalLine(const int x, const int y, const chtype ch, const int n) const
{
	std::lock_guard<std::mutex> lock(ncursesMx);

	mvwvline(win.get(), y, x, ch, n);
	wrefresh(win.get());
}

void SecondWindowController::drawCharAtPosition(const int x, const int y, const char mark, int colorPair) const
{
	std::lock_guard<std::mutex> lock(this->ncursesMx);

	wattron(win.get(), COLOR_PAIR(colorPair));
	mvwaddch(win.get(), y, x, mark);
	wattroff(win.get(), COLOR_PAIR(colorPair));

	wrefresh(win.get());
}

void SecondWindowController::clearBrick(const std::shared_ptr<Brick> brick) const
{
	std::lock_guard<std::mutex> lock(this->ncursesMx);

	for (int i = 0; i < brick->width; i++)
	{
		for (int j = 0; j < brick->height; j++)
		{
			mvwaddch(win.get(), brick->y + j, brick->x + i, ' ');
			wrefresh(win.get());
		}
	}
}

void SecondWindowController::drawBrick(const std::shared_ptr<Brick> brick) const
{
	std::lock_guard<std::mutex> lock(this->ncursesMx);

	for (int i = 0; i < brick->width; i++)
	{
		for (int j = 0; j < brick->height; j++)
		{
			wattron(win.get(), COLOR_PAIR(1));
			mvwaddch(win.get(), brick->y + j, brick->x + i, '*');
			wattroff(win.get(), COLOR_PAIR(1));

			wrefresh(win.get());
		}
	}
}


