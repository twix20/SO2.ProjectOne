// SO2.ProjectFinal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "World.h"
#include <memory>

std::shared_ptr<World> world = std::make_shared<World>();

int main()
{
	world->start();

    return 0;
}

