#pragma once
#include "Granary.h"
#include "Kitchen.h"

#include <chrono>
#include <atomic>
#include <memory>

#define WORLD_TIME_SLEEP_MS 100

class Kitchen;

class World
{
public:
	std::atomic<std::chrono::system_clock::time_point> world_time{};

	std::shared_ptr<Granary> granary;
	std::shared_ptr<Kitchen> kitchen;

	World();
	~World();

	void start();

	void print_world_time() const;
};

