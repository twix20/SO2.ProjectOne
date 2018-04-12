#pragma once
#include "curses.h"
#include "Brick.h"
#include <mutex>
#include <vector>

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

	void clearBrick(std::shared_ptr<Brick> brickToClear) const;
	void drawBrick(std::shared_ptr<Brick> brick) const;
};


