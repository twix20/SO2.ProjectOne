#include "stdafx.h"
#include "SnakeFactory.h"

#define TAIL_CHAR '*'

SnakeFactory::SnakeFactory()
{
}


SnakeFactory::~SnakeFactory()
{
}

std::unique_ptr<Snake> SnakeFactory::generateRandomSnakeInArea(const MovingArea area, const unsigned int snakeLength, std::shared_ptr<WindowController> window) const
{
	std::vector<SnakeChunk> tail;

	tail.push_back(SnakeChunk(area.topLeftX, area.topLeftY, TAIL_CHAR));

	int c = 1;
	while (tail.size() < snakeLength)
	{
		if (area.width > c)
		{
			tail.push_back(SnakeChunk(area.topLeftX + c, area.topLeftY, TAIL_CHAR));
		}

		c++;
	}

	const SnakeChunk head = tail.back();

	tail.pop_back();

	return std::make_unique<Snake>(head, tail, window);
}
