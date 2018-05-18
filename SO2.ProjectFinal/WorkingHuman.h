#pragma once
#include <chrono>
#include <memory>

class World;

class WorkingHuman
{
protected:
	std::shared_ptr<World> _world;

public:
	std::chrono::system_clock::time_point stamina_till;

	bool is_working;

	bool can_work() const;
	bool is_stamina_needed() const;

	bool try_to_eat();
	bool try_to_work();

	virtual void perform_work() = 0;
	virtual bool is_working_time(int hours) const = 0;

	WorkingHuman(std::shared_ptr<World> world);
	virtual ~WorkingHuman();
};

