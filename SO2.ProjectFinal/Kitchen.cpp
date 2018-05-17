#include "stdafx.h"
#include "Kitchen.h"
#include <algorithm>


std::shared_ptr<Stove> Kitchen::occupy_stove(Cook* cook)
{
	const auto it = std::find_if(std::begin(stoves), std::end(stoves), [](std::shared_ptr<Stove>& stove) { return stove->is_ocupied_by_cook() == false; });

	if (it != std::end(stoves))
	{
		auto v = *it;
		v->cook = cook;
		stoves.erase(it);
		return v;
	}

	return nullptr;
}

void Kitchen::leave_stove(std::shared_ptr<Stove> stove)
{
	stove->cook = nullptr;
	stoves.push_back(stove);
}

int Kitchen::get_free_stoves_quantity()
{
	return std::count_if(std::begin(stoves), std::end(stoves), [&](std::shared_ptr<Stove>& stove) {return stove->is_ocupied_by_cook() == false; });
}

Kitchen::Kitchen()
{
}


Kitchen::~Kitchen()
{
}
