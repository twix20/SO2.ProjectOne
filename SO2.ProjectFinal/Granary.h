#pragma once
#include <mutex>
#include <vector>

struct Wood
{
	int energy_value;

	Wood(const int energy)
	{
		energy_value = energy;
	}
};

struct Meat
{
	int stamina_reg_minutes;
	bool is_fried;

	Meat(int staminaRegMinutes, bool isFried)
	{
		stamina_reg_minutes = staminaRegMinutes;
		is_fried = isFried;
	}
};

class Granary
{
public:
	std::mutex mx;
	std::condition_variable cv_woods;
	std::condition_variable cv_meats;

	std::vector<std::shared_ptr<Wood>> woods;
	std::vector<std::shared_ptr<Meat>> meats;

	void add_wood(Wood wood);
	std::shared_ptr<Wood> take_one_wood();

	void add_meat(Meat meat);

	std::shared_ptr<Meat> take_fried_meat();
	std::shared_ptr<Meat> take_raw_meat();



	int raw_meats_quantity();
	int fried_meats_quantity();

	Granary();
	~Granary();
};
