#include "stdafx.h"
#include "World.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <algorithm>
#include "Woodcutter.h"


World::World()
{
	world_time.store(std::chrono::system_clock::now());
	granary = std::make_shared<Granary>();
	kitchen = std::make_shared<Kitchen>();



	granary->add_meat(Meat(10, true));
	granary->add_meat(Meat(10, false));
}

World::~World()
{
}

void World::start()
{
	std::shared_ptr<World> world_sp(this);

	woodcutters.push_back(std::make_shared<Woodcutter>(world_sp));

	std::vector<std::thread> threads;
	threads.push_back(std::thread([&]() {
		while (true)
		{
			const auto after = world_time.load() += std::chrono::seconds(1);
			world_time.store(after);

			std::this_thread::sleep_for(std::chrono::milliseconds(WORLD_TIME_SLEEP_MS));
		}
	}));

	std::for_each(std::begin(woodcutters), std::end(woodcutters), [&](auto w)
	{
		threads.push_back(std::thread([&](std::shared_ptr<Woodcutter> woodcutter) {
			while (true)
			{
				auto has_eaten = woodcutter->try_to_eat();
				auto has_choped = woodcutter->try_chop_wood();

				std::this_thread::sleep_for(std::chrono::milliseconds(WORLD_TIME_SLEEP_MS));
			}
		}, w));
	});

	while (true)
	{
		std::cout << "---------------------------------\n";
		print_world_time();
		print_granary();
		print_woodcutters();

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

void World::print_world_time() const
{
	print_time(world_time);
	std::cout << std::endl;
}


void World::print_granary() const
{
	std::lock_guard<std::mutex> lock(granary->mx);

	const auto woods_quantity = granary->woods.size();
	auto meats_quantity = granary->meats.size();

	std::cout << "Woods: " << woods_quantity << std::endl
		<< "Raw meats: " << granary->raw_meats_quantity()
		<< " Fried meats: " << granary->fried_meats_quantity() << std::endl;
}

void World::print_woodcutters()
{
	for(auto& w : woodcutters)
	{
		std::cout << "Woodcuter: Stamina needed: " << w->is_stamina_needed() << " Until ";
		print_time(w->stamina_till);
		std::cout << std::endl;
 	}
}
