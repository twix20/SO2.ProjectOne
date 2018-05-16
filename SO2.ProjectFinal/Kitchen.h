#pragma once
#include "Cook.h"
#include <memory>
#include <vector>
#include <condition_variable>

class Cook;

struct Stove
{
	int id;
	std::shared_ptr<Cook> cook;

	bool is_ocupied_by_cook() const
	{
		return !cook;
	}
};


class Kitchen
{
public:
	std::mutex mx;
	std::condition_variable cv_stoves;
	std::vector<std::shared_ptr<Stove>> stoves;


	std::shared_ptr<Stove> try_occupy_stove(std::shared_ptr<Cook> cook);
	void leave_stove(int stove_id);


	Kitchen();
	~Kitchen();
};

