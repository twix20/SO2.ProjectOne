#include "NCursesController.h"
#include <memory>
#include <string>

NCursesController::NCursesController(const int height, const int width)
{
	// Init ncurses
	initscr();
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_RED);
	init_pair(4, COLOR_GREEN, COLOR_GREEN);

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
	attron(COLOR_PAIR(1));

	auto time_string = time_point_to_string(wordl_time);

	mvprintw(0, width / 2 - time_string.size() / 2, time_string.c_str());
}
void NCursesController::print_granary(std::shared_ptr<Granary> granary)
{
	attron(COLOR_PAIR(1));

	std::lock_guard<std::mutex> lock(granary->mx);

	const std::vector<std::string> lines = {
		"Granary",
		"RawMeats: " + std::to_string(granary->raw_meats_quantity()),
		"FriedMeats: " + std::to_string(granary->fried_meats_quantity()),
		"Wood: " + std::to_string(granary->woods.size())
	};

	print_lines(4, 1, lines);
}
void NCursesController::print_woodcutters(int y, std::vector<std::shared_ptr<Woodcutter>>& woodcutters)
{
	attron(COLOR_PAIR(1));

	std::vector<std::string> header;
	header.push_back("");
	header.push_back(std::to_string(WOODCUTTER_START_JOB_HOUR) + "-" + std::to_string(WOODCUTTER_END_JOB_HOUR));
	print_rows(2, y, CELL_WIDTH, header);

	std::vector<std::string> rows;
	rows.push_back("Woodcuter:");
	rows.push_back("IsWorking:");
	rows.push_back("Wood:");
	rows.push_back("Stamina:");
	rows.push_back("Until:");

	print_rows(2, y + 1, CELL_WIDTH, rows);

	for(uint32_t i = 0; i < woodcutters.size(); i++)
	{
		auto w = woodcutters[i];

		std::vector<std::string> rows;
		rows.push_back(std::to_string(i));
		rows.push_back(std::to_string(w->is_working));
		rows.push_back(std::to_string(w->chooped_wood_so_far));
		rows.push_back(std::to_string(w->is_stamina_needed()));
		rows.push_back(time_point_to_string(w->stamina_till));

		print_rows(2, y + 2 + i, CELL_WIDTH, rows);
	}
}

void NCursesController::print_cooks(int y, const std::vector<std::shared_ptr<Cook>>& cooks)
{
	attron(COLOR_PAIR(1));

	std::vector<std::string> header;
	header.push_back("");
	header.push_back(std::to_string(COOK_START_JOB_HOUR) + "-" + std::to_string(COOK_END_JOB_HOUR));
	print_rows(2, y, CELL_WIDTH, header);


	std::vector<std::string> rows;
	rows.push_back("Cook:");
	rows.push_back("IsWorking:");
	rows.push_back("Cooked:");
	rows.push_back("Stamina:");
	rows.push_back("Until:");

	print_rows(2, y + 1, CELL_WIDTH, rows);

	for (uint32_t i = 0; i < cooks.size(); i++)
	{
		auto c = cooks[i];

		std::vector<std::string> rows;
		rows.push_back(std::to_string(i));
		rows.push_back(std::to_string(c->is_working));
		rows.push_back(std::to_string(c->has_cooked_meats_quantity));
		rows.push_back(std::to_string(c->is_stamina_needed()));
		rows.push_back(time_point_to_string(c->stamina_till));

		print_rows(2, y + 2 + i, CELL_WIDTH, rows);
	}
}

void NCursesController::print_stoves(int x, int y, std::vector<std::shared_ptr<Stove>>& stoves)
{
	mvprintw(y, x, "Stoves:");

	for (uint32_t i = 0; i < stoves.size() ; i++)
	{
		auto stove = stoves[i];

		if(stove->is_ocupied_by_cook())
			attron(COLOR_PAIR(3));
		else
			attron(COLOR_PAIR(4));

		mvprintw(y + 1, x + i + 1, " ");
	}
}

void NCursesController::print_hunters(int y, const std::vector<std::shared_ptr<Hunter>>& hunters)
{
	attron(COLOR_PAIR(1));

	std::vector<std::string> header;
	header.push_back("");
	header.push_back(std::to_string(HUNTER_START_JOB_HOUR) + "-" + std::to_string(HUNTER_END_JOB_HOUR));
	print_rows(2, y, CELL_WIDTH, header);


	std::vector<std::string> rows;
	rows.push_back("Hunter:");
	rows.push_back("IsWorking:");
	rows.push_back("Raw Meat:");
	rows.push_back("Stamina:");
	rows.push_back("Until:");

	print_rows(2, y + 1, CELL_WIDTH, rows);

	for (uint32_t i = 0; i < hunters.size(); i++)
	{
		auto h = hunters[i];

		std::vector<std::string> rows;
		rows.push_back(std::to_string(i));
		rows.push_back(std::to_string(h->is_working));
		rows.push_back(std::to_string(h->hunted_raw_meat));
		rows.push_back(std::to_string(h->is_stamina_needed()));
		rows.push_back(time_point_to_string(h->stamina_till));

		print_rows(2, y + 2 + i, CELL_WIDTH, rows);
	}

}

void NCursesController::print_all_works_performed(int all_works_performed)
{
	const std::vector<std::string> lines = {
		"All Works Performed:",
		std::to_string(all_works_performed),
	};

	print_lines(55, 2, lines);
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
	for(uint32_t i = 0; i < lines.size(); i++)
	{
		mvprintw(y + i, x, lines[i].c_str());
	}
}

void NCursesController::print_rows(int x, int y, int cell_width, std::vector<std::string> rows)
{
	for(uint32_t i = 0; i < rows.size(); i++)
	{
		mvprintw(y, x + (i * cell_width), rows[i].c_str());
	}
}