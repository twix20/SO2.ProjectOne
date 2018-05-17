#pragma once
#include "World.h"

class World;
class Cook;

class Stove
{
public:
	std::mutex mx;
	int cooking_time_ms;
	Cook* cook;
	std::shared_ptr<World> _world;

	~Stove();
	Stove(std::shared_ptr<World> world, int cooking_time);
	bool is_ocupied_by_cook();
	void cook_meat(std::shared_ptr<Meat> meat, std::shared_ptr<Wood> wood);
};

