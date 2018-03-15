#include "stdafx.h"
#include "SnakeFactory.h"
#include <xlocale>
#include <algorithm>

#define TAIL_CHAR '*'

SnakeFactory::SnakeFactory()
{
}


SnakeFactory::~SnakeFactory()
{
}

std::unique_ptr<Snake> SnakeFactory::generateRandomSnakeInArea(MovingArea& area, const int snakeLength, std::shared_ptr<WindowController> window) const
{
	if (snakeLength > area.width || snakeLength <= 0)
		throw std::invalid_argument("not supported snakeLength");

	std::vector<SnakeChunk> tail{ SnakeChunk(area.topLeftX , area.topLeftY, TAIL_CHAR) };
	while (static_cast<int>(tail.size()) < snakeLength)
	{
		tail.push_back(SnakeChunk(area.topLeftX + tail.size(), area.topLeftY, TAIL_CHAR));
	}

	const SnakeChunk head = tail.back();
	tail.pop_back();

	auto snake = std::make_unique<Snake>(head, tail, window);

	std::vector<DIRECTION> transportSnakeDirs{ S, S, S, E, E, E, E };
	std::for_each(transportSnakeDirs.begin(), transportSnakeDirs.end(), [&](DIRECTION& dir)
	{
		snake->tryToMove(dir, area);
	});

	return snake;
}
