#pragma once
#include <vector>

struct MovingArea
{
	int topLeftX, topLeftY;
	int height, width;
};

struct SnakeChunk
{
	int x, y;
	char mark;

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
	E //E must be last! cuz used in moveRandomInArea
};

class Snake
{
	SnakeChunk head;
	std::vector<SnakeChunk> tail;

public:
	Snake(SnakeChunk head, std::vector<SnakeChunk> tail);
	~Snake();

	bool tryToMove(DIRECTION dir);
	bool isMoveOverlapingTail(int x, int y);

	void moveRandomInArea(MovingArea area);
};

