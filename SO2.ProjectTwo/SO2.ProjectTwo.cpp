// SO2.Project.ProjectTwo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SecondWindowController.h"
#include "Brick.h"
#include <algorithm>
#include "../SO2.ProjectOne/Utils.h"

#define WINDOW_HEIGHT 28
#define WINDOW_WIDTH 111

std::shared_ptr<SecondWindowController> window;

std::vector<std::shared_ptr<Brick>> availableBricks;

void fallingBrickFunc(WallArea& area)
{
	while (true)
	{
		//Add brick if empty
		if(area.bricks.size() < 1)
		{
			//TODO rand x
			area.bricks.push_back(std::make_shared<Brick>(area.topLeftX + 1, area.topLeftY + 1));
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

				Utils::print_log("availableBricks: %d\n", availableBricks.size());
			}
			else
			{
				window->drawBrick(*it);
				++it;
			}


			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

	}
}

void leechingBrickFunc(WallArea& area)
{
	
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
		if(first)
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

