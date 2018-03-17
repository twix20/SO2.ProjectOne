#include "stdafx.h"
#include <algorithm>
#include <windows.h>

#include "Snake.h"
#include "WindowController.h"
#include "Utils.h"
#include "SnakeFactory.h"

Snake::Snake(const SnakeChunk head, const std::vector<SnakeChunk>& tail, const std::shared_ptr<WindowController> window)
{
	this->head = head;
	this->tail = tail;
	this->window = window;
}

Snake::~Snake()
{
}

bool Snake::tryToMove(const DIRECTION dir, MovingArea& area)
{
	auto futureX = head.x;
	auto futureY = head.y;

	switch (dir)
	{
	case N:
		futureY--;
		break;
	case S:
		futureY++;
		break;
	case W:
		futureX--;
		break;
	case E:
		futureX++;
		break;
	}

	//Check if can move
	if (isOverlapingTail(tail, futureX, futureY))
		return false;

	if (!area.isInArea(futureX, futureY))
		return false;

	//Perform move
	tail.push_back(SnakeFactory::createTailChunk(head.x, head.y));

	head = SnakeFactory::createHeadChunk(futureX, futureY);

	const SnakeChunk first = *tail.begin();
	tail.erase(tail.begin());

	window->clearPosition(first.x, first.y);
	window->drawChunk(tail.back());
	window->drawChunk(head);

	return true;
}

bool Snake::isOverlapingTail(std::vector<SnakeChunk>& tail, int x, int y)
{
	return std::any_of(begin(tail), end(tail), [&](SnakeChunk& chunk) -> bool {
		return chunk.x == x && chunk.y == y;
	});
}

void Snake::moveRandomInArea(MovingArea& area)
{
	bool moved = false;
	std::vector<DIRECTION> avalibleDirections = { N, S, W, E };
	do
	{
		const unsigned int randomIndex = Utils::random_in_range(0, avalibleDirections.size() - 1);

		//Utils::print_log("%i in thread %d\n for area %p", randomIndex, std::this_thread::get_id(), area);

		moved = tryToMove(avalibleDirections[randomIndex], area);

		if (!moved)
			avalibleDirections.erase(avalibleDirections.begin() + randomIndex);

		if (avalibleDirections.size() == 0) //can happen if snake is stuck
			break;

	} while (!moved);


}

void Snake::drawMe()
{
	window->drawChunk(head);

	for (auto& t : tail)
		window->drawChunk(t);
}


