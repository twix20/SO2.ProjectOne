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
	cv_meats.notify_one();
}

std::shared_ptr<Meat> Granary::take_fried_meat()
{
	const auto pred = [](const std::shared_ptr<Meat>& meat) { return meat->is_fried; };

	return take_meat(pred);
}

std::shared_ptr<Meat> Granary::take_raw_meat()
{
	const auto pred = [](const std::shared_ptr<Meat>& meat) { return !meat->is_fried; };

	return take_meat(pred);
}

std::shared_ptr<Wood> Granary::take_wood()
{
	const auto it = std::begin(woods);
	auto v = *it;
	woods.erase(it);
	return v;
}

std::shared_ptr<Meat> Granary::take_meat(std::function<bool(const std::shared_ptr<Meat>)> predicate)
{
	const auto it = std::find_if(std::begin(meats), std::end(meats), predicate);

	if (it != std::end(meats))
	{
		auto v = *it;

		meats.erase(it);
		return v;
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
