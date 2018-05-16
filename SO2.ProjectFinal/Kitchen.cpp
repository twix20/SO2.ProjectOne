#include "stdafx.h"
#include "Kitchen.h"


std::shared_ptr<Stove> Kitchen::try_occupy_stove(const std::shared_ptr<Cook> cook)
{
	for(auto stove : stoves)
	{
		if (!stove->is_ocupied_by_cook())
		{
			stove->cook = cook;
			return stove;
		}
	}

	return nullptr;
}

void Kitchen::leave_stove(int stove_id)
{
	for (auto stove : stoves)
	{
		if (stove->is_ocupied_by_cook() && stove->id == stove_id)
		{
			stove->cook = nullptr;
			cv_stoves.notify_one();
			break;
		}
	}
}

Kitchen::Kitchen()
{
}


Kitchen::~Kitchen()
{
}
