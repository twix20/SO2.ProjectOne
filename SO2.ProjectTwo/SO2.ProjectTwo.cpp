// SO2.Project.ProjectTwo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SecondWindowController.h"
#include "Brick.h"
#include <algorithm>
#include "WallArea.h"

#define WINDOW_HEIGHT 34
#define WINDOW_WIDTH 111

std::shared_ptr<SecondWindowController> window;

std::mutex mx;
std::condition_variable cv;
std::vector<std::shared_ptr<Brick>> availableBricks;

void fallingBrickFunc(WallArea& area)
{
	while (true)
	{
		//Add brick if empty
		if (area.bricks.size() < 3)
		{
			const int randomX = Utilss::random_in_range(area.topLeftX + 1, area.topLeftX + area.width - BRICK_WIDTH);
			area.bricks.push_back(std::make_shared<Brick>(randomX, area.topLeftY + 1));
		}

		//Perform fall
		auto it = begin(area.bricks);
		while (it != area.bricks.end())
		{
			window->clearBrick(*it);

			const bool isBrickStillInArea = area.tryMoveBrickSouth(*it);
			if (!isBrickStillInArea)
			{
				availableBricks.push_back(*it);
				it = area.bricks.erase(it);

				cv.notify_one();
			}
			else
			{
				window->drawBrick(*it);
				++it;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(7));
		}

	}
}

void leechingBrickFunc(WallArea& area)
{
	const int columns = (WINDOW_WIDTH / (BRICK_WIDTH + 1)) / 2;
	const int rows = (WINDOW_HEIGHT / (BRICK_HEIGHT + 1)) / 2;
	const int areaCapacity = rows * columns;

	while (true)
	{
		if (area.bricks.size() >= areaCapacity)
		{
			for (auto& b : area.bricks)
				window->clearBrick(b);
			area.bricks.clear();

			for (auto& b : availableBricks)
				window->clearBrick(b);
			availableBricks.clear();
			continue;
		}

		//Wait until availableBricks is not empty
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, [] {return !availableBricks.empty(); });

		auto bIt = availableBricks.begin();
		if (area.tryEmbedBrick(*bIt))
		{
			window->drawBrick(*bIt);
			bIt = availableBricks.erase(bIt);

			//Utilss::print_log("availableBricks: %d\n", availableBricks.size());
		}

		lk.unlock();
		cv.notify_one();
	}
}

int main()
{
	window = std::make_shared<SecondWindowController>(WINDOW_HEIGHT, WINDOW_WIDTH);
	auto areas = window->splitIntoAreas();

	std::vector<std::thread> concurrentThreads;

	//Start threads
	auto first = true;
	std::for_each(areas.begin(), areas.end(), [&](WallArea& a)
	{
		if (first)
		{
			first = false;
			concurrentThreads.push_back(std::thread(fallingBrickFunc, std::ref(a)));
		}
		else
		{
			concurrentThreads.push_back(std::thread(leechingBrickFunc, std::ref(a)));
		}
	});

	//Join threads
	std::for_each(concurrentThreads.begin(), concurrentThreads.end(), [](std::thread& t)
	{
		t.join();
	});

	return 0;
}

