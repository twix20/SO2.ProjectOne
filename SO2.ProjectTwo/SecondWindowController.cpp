#include "stdafx.h"
#include "SecondWindowController.h"

SecondWindowController::SecondWindowController(const int height, const int width)
{
	//Init ncurses
	initscr();
	start_color();

	init_pair(1, COLOR_BLUE, COLOR_MAGENTA);
	init_pair(2, COLOR_BLUE, COLOR_YELLOW);
	init_pair(3, COLOR_BLUE, COLOR_WHITE);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_GREEN);
	init_pair(6, COLOR_RED, COLOR_BLUE);
	init_pair(7, COLOR_RED, COLOR_RED);
	init_pair(8, COLOR_RED, COLOR_CYAN);
	init_pair(9, COLOR_RED, COLOR_MAGENTA);
	init_pair(10, COLOR_RED, COLOR_YELLOW);
	init_pair(11, COLOR_RED, COLOR_WHITE);
	init_pair(12, COLOR_CYAN, COLOR_BLACK);
	init_pair(13, COLOR_CYAN, COLOR_GREEN);
	init_pair(14, COLOR_CYAN, COLOR_BLUE);
	init_pair(15, COLOR_CYAN, COLOR_RED);
	init_pair(16, COLOR_CYAN, COLOR_CYAN);
	init_pair(17, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(18, COLOR_CYAN, COLOR_YELLOW);
	init_pair(19, COLOR_CYAN, COLOR_WHITE);
	init_pair(20, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(21, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(22, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(23, COLOR_MAGENTA, COLOR_RED);
	init_pair(24, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(25, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(26, COLOR_MAGENTA, COLOR_YELLOW);
	init_pair(27, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(28, COLOR_YELLOW, COLOR_BLACK);
	init_pair(29, COLOR_YELLOW, COLOR_GREEN);
	init_pair(30, COLOR_YELLOW, COLOR_BLUE);
	init_pair(31, COLOR_YELLOW, COLOR_RED);
	init_pair(32, COLOR_YELLOW, COLOR_CYAN);
	init_pair(33, COLOR_YELLOW, COLOR_MAGENTA);
	init_pair(34, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(35, COLOR_YELLOW, COLOR_WHITE);
	init_pair(36, COLOR_WHITE, COLOR_BLACK);
	init_pair(37, COLOR_WHITE, COLOR_GREEN);
	init_pair(38, COLOR_WHITE, COLOR_BLUE);
	init_pair(39, COLOR_WHITE, COLOR_RED);
	init_pair(40, COLOR_WHITE, COLOR_CYAN);
	init_pair(41, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(42, COLOR_WHITE, COLOR_YELLOW);
	init_pair(43, COLOR_WHITE, COLOR_WHITE);
	init_pair(44, COLOR_BLACK, COLOR_BLACK);
	init_pair(45, COLOR_BLACK, COLOR_GREEN);
	init_pair(46, COLOR_BLACK, COLOR_BLUE);
	init_pair(47, COLOR_BLACK, COLOR_RED);
	init_pair(48, COLOR_BLACK, COLOR_CYAN);
	init_pair(49, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(50, COLOR_BLACK, COLOR_YELLOW);
	init_pair(51, COLOR_BLACK, COLOR_WHITE);
	init_pair(52, COLOR_GREEN, COLOR_BLACK);
	init_pair(53, COLOR_GREEN, COLOR_GREEN);
	init_pair(54, COLOR_GREEN, COLOR_BLUE);
	init_pair(55, COLOR_GREEN, COLOR_RED);
	init_pair(56, COLOR_GREEN, COLOR_CYAN);
	init_pair(57, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(58, COLOR_GREEN, COLOR_YELLOW);
	init_pair(59, COLOR_GREEN, COLOR_WHITE);
	init_pair(60, COLOR_BLUE, COLOR_BLACK);
	init_pair(61, COLOR_BLUE, COLOR_GREEN);
	init_pair(62, COLOR_BLUE, COLOR_BLUE);
	init_pair(63, COLOR_BLUE, COLOR_RED);
	init_pair(64, COLOR_BLUE, COLOR_CYAN);

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
	//endwin();
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
			wattron(win.get(), COLOR_PAIR(brick->colorPair));
			mvwaddch(win.get(), brick->y + j, brick->x + i, '*');
			wattroff(win.get(), COLOR_PAIR(brick->colorPair));

			wrefresh(win.get());
		}
	}
}


