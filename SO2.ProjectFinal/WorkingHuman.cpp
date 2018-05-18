#include "stdafx.h"
#include "WorkingHuman.h"
#include <memory>
#include "World.h"


bool WorkingHuman::can_work() const
{
	using namespace std;
	using namespace std::chrono;

	const auto current_world_time = _world->world_time.load();
	time_t tt = system_clock::to_time_t(current_world_time);
	struct tm tmp;
	gmtime_s(&tmp, &tt);

	const auto h = tmp.tm_hour + 2;
	const auto is_work_time = is_working_time(h);

	if (is_work_time)
		return !is_stamina_needed();

	return false;
}

bool WorkingHuman::is_stamina_needed() const
{
	const auto current_world_time = _world->world_time.load();
	const auto x = std::chrono::duration_cast<std::chrono::microseconds>(stamina_till - current_world_time).count();

	return x < 0;
}

bool WorkingHuman::try_to_eat()
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

bool WorkingHuman::try_to_work()
{
	if (can_work())
	{

		perform_work();
		return true;
		
	}

	return false;
}

WorkingHuman::WorkingHuman(std::shared_ptr<World> world)
{
	_world = world;
	is_working = false;
	stamina_till = _world->world_time.load() + std::chrono::minutes(1);
}


WorkingHuman::~WorkingHuman()
{
}
