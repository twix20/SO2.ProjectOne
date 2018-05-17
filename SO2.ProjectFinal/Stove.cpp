#include "stdafx.h"
#include "Stove.h"

Stove::~Stove()
{
}

Stove::Stove(std::shared_ptr<World> world, int cooking_time)
{
	_world = world;
	cook = nullptr;
	this->cooking_time_ms = cooking_time;
}

bool Stove::is_ocupied_by_cook()
{
	std::lock_guard<std::mutex> lock(mx);

	return cook != nullptr;
}

void Stove::cook_meat(std::shared_ptr<Meat> meat)
{
	//Wait for wood
	std::unique_lock<std::mutex> lock(_world->granary->mx);
	_world->granary->cv_woods.wait(lock, [&] { return _world->granary->woods.size() > 0; });
	const auto wood = _world->granary->take_wood();
	lock.unlock();

	std::this_thread::sleep_for(std::chrono::milliseconds(wood->cookingTime));
	meat->is_fried = true;

	std::lock_guard<std::mutex> lock_granar(_world->granary->mx);
	_world->granary->add_meat(*meat);

}
