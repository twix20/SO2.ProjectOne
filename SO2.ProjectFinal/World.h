#pragma once

#include <chrono>
#include <atomic>
#include <memory>
#include "Woodcutter.h"
#include "Hunter.h"
#include "Granary.h"
#include "Kitchen.h"

#define WOODCUTTER_START_JOB_HOUR 8
#define WOODCUTTER_END_JOB_HOUR 16

#define COOK_START_JOB_HOUR 5
#define COOK_END_JOB_HOUR 20

#define COOKING_MEAT_TIME_SLEEP_MS 1000
#define WORLD_TIME_SLEEP_MS 1

#define WORKING_HUMAN_THREAD_TIME_SLEEP_MS 100
#define PRINTING_THREAD_INTERVAL_MS 100

class Cook;
class Woodcutter;
class Kitchen;
class Cook;

class World
{
public:
	std::atomic<std::chrono::system_clock::time_point> world_time{};

	std::shared_ptr<Granary> granary;
	std::shared_ptr<Kitchen> kitchen;

	std::vector<std::shared_ptr<Woodcutter>> woodcutters;
	std::vector<std::shared_ptr<Cook>> cooks;
	std::vector<std::shared_ptr<Hunter>> hunters;

	World();
	~World();

	void start();
};

