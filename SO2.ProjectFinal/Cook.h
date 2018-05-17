#pragma once
#include <memory>
#include "World.h"

class World;

class Cook
{
private:
	std::shared_ptr<World> _world;

public:
	bool try_cook();
	bool can_work();

	bool is_cooking;
	int has_cooked_meats_quantity;

	Cook(std::shared_ptr<World> world);
	~Cook();
};

