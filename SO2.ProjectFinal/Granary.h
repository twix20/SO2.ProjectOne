#pragma once
#include <mutex>
#include <vector>

struct Wood
{
	int cookingTime;

	Wood(const int cookingTimeMs)
	{
		cookingTime = cookingTimeMs;
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
private:
	std::shared_ptr<Meat> take_meat(std::function<bool(const std::shared_ptr<Meat>)> predicate);

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

	std::shared_ptr<Wood> take_wood();



	int raw_meats_quantity();
	int fried_meats_quantity();

	Granary();
	~Granary();
};
