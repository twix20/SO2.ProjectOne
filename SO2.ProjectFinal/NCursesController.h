#pragma once
#include "curses.h"
#include "Granary.h"
#include "Woodcutter.h"

class NCursesController
{
private:
	int height, width;
	std::shared_ptr<WINDOW> win;

	std::string time_point_to_string(std::chrono::system_clock::time_point & tp);
	void print_lines(int x, int y, std::vector<std::string> lines);

public:
	NCursesController(const int height, const int width);
	~NCursesController();

	void print_world_time(std::chrono::system_clock::time_point wordl_time);
	void print_granary(std::shared_ptr<Granary> granary);
	void print_woodcutters(std::vector<std::shared_ptr<Woodcutter>>& woodcutters);
	void print_cooks(const std::vector<std::shared_ptr<Cook>>& cooks);
};

