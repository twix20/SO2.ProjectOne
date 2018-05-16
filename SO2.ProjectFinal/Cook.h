#pragma once
#include <memory>
#include "World.h"

class World;

class Cook
{
public:
	Cook(std::shared_ptr<World> world);
	~Cook();
};

