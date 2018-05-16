#pragma once
#include <chrono>
#include "World.h"

class World;

class Woodcutter
{
private:
	std::shared_ptr<World> _world;

public:
	std::chrono::system_clock::time_point stamina_till;


	bool try_to_eat();
	bool try_chop_wood() const;


	bool is_stamina_needed() const;


	Woodcutter(std::shared_ptr<World> world);
	~Woodcutter();
};

