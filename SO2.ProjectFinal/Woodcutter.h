#pragma once
#include "World.h"
#include "WorkingHuman.h"

class Woodcutter : public WorkingHuman
{
public:
	Woodcutter(std::shared_ptr<World> world);
	~Woodcutter();

	void perform_work() override;
	bool is_working_time(int hours) const override;
};

