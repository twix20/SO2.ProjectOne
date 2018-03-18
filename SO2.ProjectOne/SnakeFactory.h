#pragma once
#include <memory>
#include "Snake.h"

namespace SnakeFactory {
	class SnakeFactory
	{
	public:
		SnakeFactory();
		~SnakeFactory();

		std::unique_ptr<Snake> generateRandomSnakeInArea(MovingArea& area, int snakeLength, std::shared_ptr<WindowController> window) const;
	};

	inline SnakeChunk createHeadChunk(const int x, const int y)
	{
		return SnakeChunk(x, y, 'H', 1);
	}

	inline SnakeChunk createTailChunk(const int x, const int y)
	{
		return SnakeChunk(x, y, '*', 2);
	}
}

