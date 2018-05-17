#pragma once
#include <memory>
#include <vector>
#include <condition_variable>
#include "Stove.h"
#include "Cook.h" 

class World;
class Cook;
class Stove;
struct Meat;

class Kitchen
{
public:
	std::mutex mx;
	std::condition_variable cv_stoves;
	std::vector<std::shared_ptr<Stove>> stoves;

	std::shared_ptr<Stove> occupy_stove(Cook* cook);
	void leave_stove(std::shared_ptr<Stove> stove);

	int get_free_stoves_quantity();

	Kitchen();
	~Kitchen();
};

