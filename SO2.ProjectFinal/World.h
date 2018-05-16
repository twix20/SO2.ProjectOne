#pragma once
#include "Granary.h"
#include "Kitchen.h"

#include <chrono>
#include <atomic>
#include <memory>
#include "Woodcutter.h"

#define WORLD_TIME_SLEEP_MS 100

class Woodcutter;
class Kitchen;

class World
{
public:
	std::atomic<std::chrono::system_clock::time_point> world_time{};

	std::shared_ptr<Granary> granary;
	std::shared_ptr<Kitchen> kitchen;

	std::vector<std::shared_ptr<Woodcutter>> woodcutters;

	World();
	~World();

	void set_woodcutters(std::vector<std::shared_ptr<Woodcutter>> woodcutters);

	void start();

	void print_world_time() const;
	void print_granary() const;
	void print_woodcutters();
};

