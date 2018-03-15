#pragma once
#include "curses.h"
#include <mutex>

class WindowController
{
private:
	int height, width;
	std::shared_ptr<WINDOW> win;
	mutable std::mutex ncursesMx;

public:
	WindowController(int height, int width);
	~WindowController();

	void clearPosition(int x, int y) const;
	void drawCharAtPosition(int x, int y, char mark) const;
};

