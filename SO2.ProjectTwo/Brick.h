#pragma once
#include <vector>
#include <memory>


class Brick
{

public:
	int x, y;
	int width, height;

	Brick(const int x, const int y)
	{
		this->x = x;
		this->y = y;

		this->width = 3;
		this->height = 2;
	}
};

struct WallArea
{
	int topLeftX;
	int topLeftY;
	int height;
	int width;

	std::vector<std::shared_ptr<Brick>> bricks;

	//returns true if moved out of area
	bool tryMoveBrickSouth(const std::shared_ptr<Brick> brick) const
	{
		if(!isInArea(brick->x, brick->y + brick->height))
		{
			return false;
		}

		brick->y++;
		return true;
	}

	bool isInArea(const int x, const int y) const
	{
		return (x > topLeftX && x < topLeftX + width) &&
			(y > topLeftY && y < topLeftY + height);
	}
};


