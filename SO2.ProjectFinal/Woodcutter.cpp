#include "stdafx.h"
#include "Woodcutter.h"


bool Woodcutter::try_to_eat()
{
	if (is_stamina_needed())
	{
		// Wait until fried meat in granary
		std::unique_lock<std::mutex> lk(_world->granary->mx);
		_world->granary->cv_meats.wait(lk, [&] {return _world->granary->fried_meats_quantity() > 0; });

		std::shared_ptr<Meat> m = _world->granary->take_fried_meat();

		const auto current_world_time = _world->world_time.load();
		this->stamina_till = current_world_time + std::chrono::minutes(m->stamina_reg_minutes);

		return true;
	}

	return false;
}

bool Woodcutter::try_chop_wood() const
{
	//TODO: dodaj moze rabac drewno w przedzialach czasu swiata tylko
	const auto current_world_time = _world->world_time.load();

	if (current_world_time <= stamina_till)
	{
		std::lock_guard<std::mutex> lock(_world->granary->mx);

		_world->granary->add_wood(Wood(10));


		return true;
	}

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
