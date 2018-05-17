#pragma once
#include <memory>
#include "World.h"
#include "WorkingHuman.h"

class Cook : public WorkingHuman
{
public:
	void perform_work() override;
	bool is_working_time(int hours) const override;

	int has_cooked_meats_quantity;

	Cook(std::shared_ptr<World> world);
	~Cook();
};

