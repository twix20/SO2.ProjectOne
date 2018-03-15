// SO2.ProjectOne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WindowController.h"
#include "Snake.h"
#include "SnakeFactory.h"

#include <memory>
#include <vector>

#define WINDOW_HEIGHT 28
#define WINDOW_WIDTH 110
#define SNAKE_INIT_LENGTH 5

std::shared_ptr<WindowController> window;

std::vector<MovingArea> splitRectangleToAreas(const unsigned int height, const unsigned int width)
{
	std::vector<MovingArea> result;

	const int sharedHeight = height / 2;
	const int sharedWidth = width / 2;

	result.push_back({ 0,            0,           sharedHeight, sharedWidth });
	result.push_back({ 0,            sharedHeight, sharedHeight, sharedWidth });
	result.push_back({ sharedWidth, 0,            sharedHeight, sharedWidth });
	result.push_back({ sharedWidth, sharedHeight,  sharedHeight, sharedWidth });

	window->drawHorizontalLine(1, height / 2, '_', WINDOW_WIDTH - 2);
	window->drawVerticalLine(width / 2, 1, '|', WINDOW_HEIGHT - 2);

	const int offest = 2;
	for(auto& a : result)
	{
		a.topLeftX += offest;
		a.width -= offest;

		a.topLeftY += offest;
		a.height -= offest * 2;
	}

	return result;
}

int main()
{
	window = std::make_shared<WindowController>(WINDOW_HEIGHT, WINDOW_WIDTH);

	std::vector<MovingArea> areas = splitRectangleToAreas(WINDOW_HEIGHT, WINDOW_WIDTH);

	std::vector<std::thread> movingSnakeThreads;
	const auto snakeFactory = std::make_unique<SnakeFactory>();

	for (auto& area : areas) {
		std::unique_ptr<Snake> snake = snakeFactory->generateRandomSnakeInArea(area, SNAKE_INIT_LENGTH, window);

		movingSnakeThreads.push_back(std::thread([](MovingArea& area, std::unique_ptr<Snake> snake)
		{
			snake->drawMe();

			while (true)
			{
				snake->moveRandomInArea(area);

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}, std::ref(area), std::move(snake)));
	}

	for (auto& t : movingSnakeThreads)
		t.join();

	return 0;
}

