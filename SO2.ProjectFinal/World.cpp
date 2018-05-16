#include "stdafx.h"
#include "World.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>


World::World()
{
	world_time.store(std::chrono::system_clock::now());
	granary = std::make_shared<Granary>();
	kitchen = std::make_shared<Kitchen>();
}


World::~World()
{
}

void World::start()
{
	std::thread thread_time_world = std::thread([&]() {
		while(true)
		{
			const auto after = world_time.load() += std::chrono::seconds(1);
			world_time.store(after);

			std::this_thread::sleep_for(std::chrono::milliseconds(WORLD_TIME_SLEEP_MS));
		}
		std::cout << "thread function\n";
	});



	while (true)
	{
		print_world_time();

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	thread_time_world.join();
}

void World::print_world_time() const
{
	auto in_time_t = std::chrono::system_clock::to_time_t(world_time);
	std::tm buf{};
	localtime_s(&buf, &in_time_t);
	std::cout << std::put_time(&buf, "%Y-%m-%d %X") << std::endl;
}
