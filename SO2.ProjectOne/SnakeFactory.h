#pragma once
#include <memory>
#include "Snake.h"

class SnakeFactory
{
public:
	SnakeFactory();
	~SnakeFactory();

	std::unique_ptr<Snake> generateRandomSnakeInArea(MovingArea& area, int snakeLength, std::shared_ptr<WindowController> window) const;
};

