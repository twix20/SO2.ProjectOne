#include "stdafx.h"
#include "World.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <algorithm>
#include "Woodcutter.h"
#include "NCursesController.h"


World::World()
{
	world_time.store(std::chrono::system_clock::now());
	granary = std::make_shared<Granary>();
	kitchen = std::make_shared<Kitchen>();

	for(int i = 0; i < 500; i++)
		granary->add_meat(Meat(180, true));

	for (int i = 0; i < 300; i++)
		granary->add_meat(Meat(150, false));

	for (int i = 0; i < 300; i++)
		granary->add_wood(Wood(1500));
}

World::~World()
{
}

void World::start()
{
	std::shared_ptr<NCursesController> ncurses_controller = std::make_shared<NCursesController>(100, 120);

	std::shared_ptr<World> world_sp(this);

	for (int i = 0; i < 5; i++)
		kitchen->stoves.push_back(std::make_shared<Stove>(world_sp, COOKING_MEAT_TIME_SLEEP_MS));

	for (int i = 0; i < 17; i++)
		woodcutters.push_back(std::make_shared<Woodcutter>(world_sp));

	for (int i = 0; i < 12; i++)
		cooks.push_back(std::make_shared<Cook>(world_sp));

	std::vector<std::shared_ptr<WorkingHuman>> working_humans;
	working_humans.insert(working_humans.end(), woodcutters.begin(), woodcutters.end());
	working_humans.insert(working_humans.end(), cooks.begin(), cooks.end());

	std::vector<std::thread> threads;
	//WORLD TIME THREAD
	threads.push_back(std::thread([&]() {
		while (true)
		{
			const auto after = world_time.load() += std::chrono::seconds(2);
			world_time.store(after);

			std::this_thread::sleep_for(std::chrono::milliseconds(WORLD_TIME_SLEEP_MS));
		}
	}));

	//working_humans THREADS
	std::for_each(std::begin(working_humans), std::end(working_humans), [&](std::shared_ptr<WorkingHuman> w)
	{
		threads.push_back(std::thread([&](std::shared_ptr<WorkingHuman> working_human) {
			while (true)
			{
				auto has_eaten = working_human->try_to_eat();
				auto has_worked = working_human->try_to_work();

				std::this_thread::sleep_for(std::chrono::milliseconds(WORKING_HUMAN_THREAD_TIME_SLEEP_MS));
			}
		}, w));
	});

	//PRINTIN THREAD
	threads.push_back(std::thread([&]() {
		while (true)
		{
			clear();

			ncurses_controller->print_world_time(world_time.load());
			ncurses_controller->print_granary(granary);
			ncurses_controller->print_stoves(30, 2, kitchen->stoves);
			ncurses_controller->print_woodcutters(5, woodcutters);
			ncurses_controller->print_cooks(woodcutters.size() + 7, cooks);

			//std::lock_guard<std::mutex> lock_granary(granary->mx);

			//const auto after = world_time.load() += std::chrono::seconds(1);
			//world_time.store(after);

			refresh();

			std::this_thread::sleep_for(std::chrono::milliseconds(PRINTING_THREAD_INTERVAL_MS));
		}
	}));
	
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	std::for_each(threads.begin(), threads.end(), [](std::thread& t) {t.join(); });
}

void print_time(std::chrono::system_clock::time_point tp)
{
	auto in_time_t = std::chrono::system_clock::to_time_t(tp);
	std::tm buf{};
	localtime_s(&buf, &in_time_t);
	std::cout << std::put_time(&buf, "%Y-%m-%d %X");
}