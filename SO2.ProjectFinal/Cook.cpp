#include "stdafx.h"
#include "Cook.h"

void Cook::perform_work()
{
	//Wait for rawMeat
	std::unique_lock<std::mutex> lock_granary(_world->granary->mx);
	_world->granary->cv_meats.wait(lock_granary, [&] {return _world->granary->raw_meats_quantity() > 0; });
	const auto meat = _world->granary->take_raw_meat();
	lock_granary.unlock();

	// Wait until free stove
	std::unique_lock<std::mutex> lock_kitchen(_world->kitchen->mx);
	_world->kitchen->cv_stoves.wait(lock_kitchen, [&] {return _world->kitchen->get_free_stoves_quantity() > 0; });
	auto stove = _world->kitchen->occupy_stove(this);
	lock_kitchen.unlock();

	//Cook
	std::unique_lock<std::mutex> lock(stove->mx);
	is_cooking = true;
	stove->cook_meat(meat);
	has_cooked_meats_quantity += 1;
	lock.unlock();

	//Leave stove
	std::unique_lock<std::mutex> lock_kitchen2(_world->kitchen->mx);
	_world->kitchen->leave_stove(stove);
	lock_kitchen2.unlock();
	_world->kitchen->cv_stoves.notify_one();
}

bool Cook::is_working_time(int hours) const
{
	return hours >= COOK_START_JOB_HOUR && hours <= COOK_END_JOB_HOUR;
}

Cook::Cook(std::shared_ptr<World> world): WorkingHuman(world)
{
	is_cooking = false;
	has_cooked_meats_quantity = 0;
}

Cook::~Cook()
{
}
