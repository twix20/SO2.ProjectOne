#pragma once
#include <mutex>
#include <vector>

struct Wood
{
	int energy_value;
};

struct Meat
{
	int staminaRegeneration;
	bool is_fried;
};

class Granary
{
public:
	std::mutex mx;
	std::condition_variable cv_woods;
	std::condition_variable cv_meats;

	std::vector<Wood> woods;
	std::vector<Meat> meats;

	void add_wood(Wood wood);
	Wood take_one_wood();

	Granary();
	~Granary();
};
