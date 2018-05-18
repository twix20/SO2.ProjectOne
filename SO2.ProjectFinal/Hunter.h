#pragma once
#include "WorkingHuman.h"

class Hunter : public WorkingHuman
{
public:

	int hunted_raw_meat;

	Hunter(std::shared_ptr<World> world);
	~Hunter();

	void perform_work() override;
	bool is_working_time(int hours) const override;
};

