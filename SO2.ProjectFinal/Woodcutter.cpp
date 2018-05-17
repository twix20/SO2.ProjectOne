#include "stdafx.h"
#include "Woodcutter.h"


bool Woodcutter::try_to_eat()
{
	if (is_stamina_needed())
	{
		// Wait until fried meat in granary
		std::unique_lock<std::mutex> lk(_world->granary->mx);
		_world->granary->cv_meats.wait(lk, [&] {return _world->granary->fried_meats_quantity() > 0; });

		const std::shared_ptr<Meat> m = _world->granary->take_fried_meat();

		this->stamina_till += std::chrono::minutes(m->stamina_reg_minutes);

		return true;
	}

	return false;
}

bool Woodcutter::try_chop_wood() const
{
	if (can_work())
	{
		std::lock_guard<std::mutex> lock(_world->granary->mx);
		_world->granary->add_wood(Wood(3000));//cooking time TODO: zmien na random
		return true;
	}

	return false;
}

bool Woodcutter::can_work() const
{
	using namespace std;
	using namespace std::chrono;

	const auto current_world_time = _world->world_time.load();
	time_t tt = system_clock::to_time_t(current_world_time);
	struct tm tmp;
	gmtime_s(&tmp, &tt);

	//can work between 8-16
	auto h = tmp.tm_hour + 2;
	if (h >= WOODCUTTER_START_JOB_HOUR && h <= WOODCUTTER_END_JOB_HOUR)
		return !is_stamina_needed();

	return false;
}

bool Woodcutter::is_stamina_needed() const
{
	const auto current_world_time = _world->world_time.load();

	const auto x =  std::chrono::duration_cast<std::chrono::microseconds>(stamina_till - current_world_time).count();

	return x < 0;
}

Woodcutter::Woodcutter(std::shared_ptr<World> world)
{
	_world = world;
	stamina_till = _world->world_time.load() + std::chrono::minutes(1);
}

Woodcutter::~Woodcutter()
{
}
