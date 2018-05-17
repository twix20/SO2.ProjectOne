#include "stdafx.h"
#include "NCursesController.h"
#include <memory>
#include <string>


NCursesController::NCursesController(const int height, const int width)
{
	// Init ncurses
	initscr();
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	this->height = height;
	this->width = width;

	win = std::shared_ptr<WINDOW>(newwin(height, width, 1, 1));

	refresh();
	//Create box border
	box(win.get(), 0, 0);
}


NCursesController::~NCursesController()
{
	//Dispose ncurses
	endwin();
}

void NCursesController::print_world_time(std::chrono::system_clock::time_point wordl_time)
{
	auto time_string = time_point_to_string(wordl_time);

	mvprintw(0, width / 2 - time_string.size() / 2, time_string.c_str());
}
void NCursesController::print_granary(std::shared_ptr<Granary> granary)
{
	std::lock_guard<std::mutex> lock(granary->mx);

	const std::vector<std::string> lines = {
		"Granary",
		"RawMeats: " + std::to_string(granary->raw_meats_quantity()),
		"FriedMeats: " + std::to_string(granary->fried_meats_quantity()),
		"Woods: " + std::to_string(granary->woods.size())
	};

	print_lines(4, 1, lines);
}
void NCursesController::print_woodcutters(std::vector<std::shared_ptr<Woodcutter>>& woodcutters)
{
	std::vector<std::string> lines = {"Woodcutters " + std::to_string(WOODCUTTER_START_JOB_HOUR) + "-" + std::to_string(WOODCUTTER_END_JOB_HOUR) };

	for(auto& w : woodcutters)
	{
		lines.push_back("Woodcuter:");
		lines.push_back("\tIsWorking: " + std::to_string(w->can_work()));
		lines.push_back("\tStamina needed: " + std::to_string(w->is_stamina_needed()));
		lines.push_back("\tUntil " + time_point_to_string(w->stamina_till));
	}

	print_lines(2, 6, lines);
}

void NCursesController::print_cooks(const std::vector<std::shared_ptr<Cook>>& cooks)
{
	std::vector<std::string> lines = { "Cooks " + std::to_string(COOK_START_JOB_HOUR) + "-" + std::to_string(COOK_END_JOB_HOUR) };

	for (auto& c : cooks)
	{
		lines.push_back("Cook:");
		lines.push_back("\tIsWorking: " + std::to_string(c->can_work()));
		lines.push_back("\tCooked so far: " + std::to_string(c->has_cooked_meats_quantity));
		lines.push_back("\tStamina needed: " + std::to_string(c->is_stamina_needed()));
		lines.push_back("\tUntil " + time_point_to_string(c->stamina_till));
	}

	print_lines(35, 6, lines);
}


std::string NCursesController::time_point_to_string(std::chrono::system_clock::time_point &tp)
{
	using namespace std;
	using namespace std::chrono;

	auto ttime_t = system_clock::to_time_t(tp);

	struct tm timeinfo;
	localtime_s(&timeinfo, &ttime_t);

	char date_time_format[] = "%Y.%m.%d %H:%M:%S";

	char time_str[] = "yyyy.mm.dd.HH-MM.SS.fff";

	strftime(time_str, strlen(time_str), date_time_format, &timeinfo);

	string result(time_str);

	return result;
}


void NCursesController::print_lines(int x, int y, std::vector<std::string> lines)
{
	for(int i = 0; i < lines.size(); i++)
	{
		mvprintw(y + i, x, lines[i].c_str());
	}
}