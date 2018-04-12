// SO2.Project.ProjectTwo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SecondWindowController.h"
#include "Brick.h"
#include <algorithm>
#include "WallArea.h"

#define WINDOW_HEIGHT 37
#define WINDOW_WIDTH 111

std::shared_ptr<SecondWindowController> window;


std::mutex mx;
std::condition_variable cv;
std::vector<Brick*> availableBricks;

bool shouldClear = false;


void fallingBrickFunc(WallArea& area)
{
	while (true)
	{
		//Add brick if empty
		if(area.bricks.size() < 1)
		{
			//TODO rand x
			area.bricks.push_back(new Brick(area.topLeftX + 1, area.topLeftY + 1));
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

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

	}
}

void leechingBrickFunc(WallArea& area)
{
	while(true)
	{
		//Wait until availableBricks is not empty
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, [] {return !availableBricks.empty(); });

		if (availableBricks.size() >= 2)
		{
			shouldClear = true;
			continue;
		}

		const auto bIt = availableBricks.begin();
		if(area.tryEmbedBrick(*bIt))
		{
			//Utilss::print_log("Area: x:%d y:%d wsadzam x:%d y:%d\n", area.topLeftX, area.topLeftY, (*bIt)->x, (*bIt)->y);
			window->drawBrick(*bIt);
			availableBricks.erase(bIt);
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

