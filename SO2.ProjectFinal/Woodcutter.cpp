#include "stdafx.h"
#include "Woodcutter.h"


Woodcutter::Woodcutter(std::shared_ptr<World> world): WorkingHuman(world)
{
}

Woodcutter::~Woodcutter()
{
}

void Woodcutter::perform_work()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	std::lock_guard<std::mutex> lock(_world->granary->mx);
	_world->granary->add_wood(Wood(3000));//cooking time TODO: zmien na random
}

bool Woodcutter::is_working_time(int hours) const
{
	return hours >= WOODCUTTER_START_JOB_HOUR && hours <= WOODCUTTER_END_JOB_HOUR;
}
