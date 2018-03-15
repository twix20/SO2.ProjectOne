#pragma once
#include <memory>
#include "Snake.h"

class SnakeFactory
{
public:
	SnakeFactory();
	~SnakeFactory();

	std::unique_ptr<Snake> generateRandomSnakeInArea(MovingArea area, const unsigned int  snakeLength, std::shared_ptr<WindowController> window) const;
};

