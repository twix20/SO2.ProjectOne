// SO2.ProjectFinal.cpp : Defines the entry point for the console application.
//

#include "World.h"
#include <memory>

int main()
{
	std::shared_ptr<World> world = std::make_shared<World>();

	world->start();

    return 0;
}

