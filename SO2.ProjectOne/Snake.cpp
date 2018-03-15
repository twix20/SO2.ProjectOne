#include "stdafx.h"
#include "Snake.h"
#include <algorithm>

Snake::Snake(const SnakeChunk head, const std::vector<SnakeChunk>& tail)
{
	this->head = head;
	this->tail = tail;
}

Snake::~Snake()
{
}

bool Snake::tryToMove(const DIRECTION dir)
{
	auto futureX = head.x;
	auto futureY = head.y;

	switch (dir)
	{
	case N:
		futureY++;
		break;
	case S:
		futureY--;
		break;
	case W:
		futureX--;
		break;
	case E:
		futureY++;
		break;
	}

	//Check if can move

	if (isMoveOverlapingTail(futureX, futureY))
		return false;

	//Perform move
	tail.insert(tail.begin(), head);
	tail.pop_back();

	head.x = futureX;
	head.y = futureY;

	return true;
}

bool Snake::isMoveOverlapingTail(const int futureX, const int futureY)
{
	return std::any_of(begin(tail), end(tail), [&](SnakeChunk& chunk) -> bool {
		return chunk.x == futureX && chunk.y == futureY;
	});
}

void Snake::moveRandomInArea(MovingArea area)
{
	DIRECTION randomDirection;
	do
	{
		randomDirection = static_cast<DIRECTION>(rand() % E);
	} while (tryToMove(randomDirection));
}


