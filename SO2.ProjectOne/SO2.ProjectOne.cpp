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

int main()
{
	window = std::make_shared<WindowController>(WINDOW_HEIGHT, WINDOW_WIDTH);

	std::vector<MovingArea> areas = window->splitIntoAreas();

	std::vector<std::thread> movingSnakeThreads;
	const auto snakeFactory = std::make_unique<SnakeFactory::SnakeFactory>();

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

