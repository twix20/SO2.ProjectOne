#pragma once
#include <vector>
#include <memory>

class WindowController;

struct MovingArea
{
	unsigned int topLeftX;
	unsigned int topLeftY;
	unsigned int height;
	unsigned int width;

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

	SnakeChunk(): x(0), y(0), mark(0)
	{
	}

	SnakeChunk(const int x, const int y, const char m)
	{
		this->x = x;
		this->y = y;
		this->mark = m;
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

