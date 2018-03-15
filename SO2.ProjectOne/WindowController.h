#pragma once
#include "curses.h"
#include <mutex>
#include "Snake.h"

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

	void drawHorizontalLine(int x, int y, chtype ch, int n) const;
	void drawVerticalLine(int x, int y, chtype ch, int n) const;

	void drawCharAtPosition(int x, int y, char mark) const;
	void drawChunk(SnakeChunk& chunk) const;
	void drawChunks(std::vector<SnakeChunk>& chunks) const;
};

