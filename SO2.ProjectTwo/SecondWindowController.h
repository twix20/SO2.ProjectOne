#pragma once
#include "curses.h"
#include <mutex>
#include <vector>

#include "Brick.h"
#include "WallArea.h"

class SecondWindowController
{
private:
	int height, width;
	std::shared_ptr<WINDOW> win;
	mutable std::mutex ncursesMx;

public:
	SecondWindowController(int height, int width);
	~SecondWindowController();

	std::vector<WallArea> splitIntoAreas() const;

	void clearPosition(int x, int y) const;

	void drawHorizontalLine(int x, int y, chtype ch, int n) const;
	void drawVerticalLine(int x, int y, chtype ch, int n) const;

	void drawCharAtPosition(int x, int y, char mark, int colorPair) const;

	void clearBrick(Brick* brickToClear) const;
	void drawBrick(Brick* brick) const;
};


