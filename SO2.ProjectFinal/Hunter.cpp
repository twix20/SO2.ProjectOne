#include "stdafx.h"
#include "Hunter.h"
#include "World.h"


Hunter::Hunter(std::shared_ptr<World> world): WorkingHuman(world)
{
	hunted_raw_meat = 0;
}

Hunter::~Hunter()
{
}

void Hunter::perform_work()
{
	is_working = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	std::lock_guard<std::mutex> lock(_world->granary->mx);
	hunted_raw_meat += 1;
	_world->granary->add_meat(Meat(140, false));//cooking time TODO: zmien na random
	is_working = false;
}

bool Hunter::is_working_time(int hours) const
{
	return hours >= HUNTER_START_JOB_HOUR && hours <= HUNTER_END_JOB_HOUR;
}
