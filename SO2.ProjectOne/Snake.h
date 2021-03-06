#pragma once
#include <vector>
#include <memory>

class WindowController;

struct MovingArea
{
	int topLeftX;
	int topLeftY;
	int height;
	int width;

	bool isInArea(const int x, const int y) const
	{
		return (x > topLeftX && x < topLeftX + width) &&
			   (y > topLeftY && y < topLeftY + height);
	}
};

struct SnakeChunk
{
	int x, y;
	char mark;
	int colorPair;

	SnakeChunk(): x(0), y(0), mark(0), colorPair(0)
	{
	}

	SnakeChunk(const int x, const int y, const char m, const int colorPair)
	{
		this->x = x;
		this->y = y;
		this->mark = m;
		this->colorPair = colorPair;
	}
};

enum DIRECTION
{
	N, 
	S, 
	W, 
	E 
};

class Snake
{
	// *****H
	// H - head
	SnakeChunk head;
	std::vector<SnakeChunk> tail;

	std::shared_ptr<WindowController> window;

public:
	Snake(const SnakeChunk head, const std::vector<SnakeChunk>& tail, std::shared_ptr<WindowController> window);
	~Snake();

	bool tryToMove(DIRECTION dir, MovingArea& area);

	static bool isOverlapingTail(std::vector<SnakeChunk>& tail, int x, int y);

	void moveRandomInArea(MovingArea& area);

	void drawMe();
};

