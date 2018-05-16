#include "stdafx.h"
#include "Granary.h"
#include <algorithm>


Granary::Granary()
{
}


Granary::~Granary()
{
}

void Granary::add_wood(Wood wood)
{
	woods.push_back(std::make_shared<Wood>(wood));
	cv_woods.notify_one();
}

std::shared_ptr<Wood> Granary::take_one_wood()
{
	const auto w = woods.front();
	cv_woods.notify_one();

	return w;
}

void Granary::add_meat(Meat meat)
{
	meats.push_back(std::make_shared<Meat>(meat));
}

std::shared_ptr<Meat> Granary::take_fried_meat()
{
	const auto it = std::find_if(std::begin(meats), std::end(meats), [](const std::shared_ptr<Meat>& meat) { return meat->is_fried; });

	if(it != std::end(meats))
	{
		auto v = *it;
		if (v->is_fried)
		{
			meats.erase(it);
			return v;
		}
	}

	return nullptr;
}

int Granary::raw_meats_quantity()
{
	return std::count_if(meats.begin(), meats.end(), [](const std::shared_ptr<Meat> m) { return !m->is_fried; });
}

int Granary::fried_meats_quantity()
{
	return std::count_if(meats.begin(), meats.end(), [](const std::shared_ptr<Meat> m) { return m->is_fried; });
}
