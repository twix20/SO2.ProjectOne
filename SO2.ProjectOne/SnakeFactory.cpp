#include "stdafx.h"
#include "SnakeFactory.h"

#define TAIL_CHAR '*'

SnakeFactory::SnakeFactory()
{
}


SnakeFactory::~SnakeFactory()
{
}

std::unique_ptr<Snake> SnakeFactory::generateRandomSnakeInArea(const MovingArea area, const int snakeLength, std::shared_ptr<WindowController> window) const
{
	if(snakeLength > area.width || snakeLength <= 0)
		throw std::invalid_argument("not supported snakeLength");

	std::vector<SnakeChunk> tail;

	int c = 1;
	tail.push_back(SnakeChunk(area.topLeftX + c, area.topLeftY, TAIL_CHAR));

	while (tail.size() < snakeLength)
	{
		c++;

		tail.push_back(SnakeChunk(area.topLeftX + c, area.topLeftY + 1, TAIL_CHAR));
	}

	const SnakeChunk head = tail.back();

	tail.pop_back();

	return std::make_unique<Snake>(head, tail, window);
}
