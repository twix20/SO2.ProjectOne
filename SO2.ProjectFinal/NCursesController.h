#pragma once
#include "curses.h"
#include "Granary.h"
#include "Woodcutter.h"

#define CELL_WIDTH 13

class NCursesController
{
private:
	int height, width;
	std::shared_ptr<WINDOW> win;

	std::string time_point_to_string(std::chrono::system_clock::time_point & tp);
	void print_lines(int x, int y, std::vector<std::string> lines);
	void print_rows(int x, int y, int cell_width, std::vector<std::string> rows);

public:
	NCursesController(const int height, const int width);
	~NCursesController();

	void print_world_time(std::chrono::system_clock::time_point wordl_time);
	void print_granary(std::shared_ptr<Granary> granary);
	void print_woodcutters(int y, std::vector<std::shared_ptr<Woodcutter>>& woodcutters);
	void print_cooks(int y, const std::vector<std::shared_ptr<Cook>>& cooks);
	void print_stoves(int x, int y, std::vector<std::shared_ptr<Stove>>& stoves);
	void print_hunters(int y, const std::vector<std::shared_ptr<Hunter>>& hunters);
	void print_all_works_performed(int all_works_performed);
};

