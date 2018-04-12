#pragma once
#include <vector>
#include "Brick.h"
#include "Utilss.h"

struct WallArea
{
	int topLeftX;
	int topLeftY;
	int height;
	int width;

	std::vector<Brick*> bricks;

	//returns true if moved out of area
	bool tryMoveBrickSouth(Brick* brick) const
	{
		if (!isInArea(brick->x, brick->y + brick->height))
		{
			return false;
		}

		brick->y++;
		return true;
	}

	bool tryEmbedBrick(Brick* brick)
	{
		Utilss::print_log("All bricks in area: x:%d y:%d\n", topLeftX, topLeftY);
		for (auto it = begin(bricks); it != end(bricks); ++it)
			Utilss::print_log("Brick: x:%d y:%d\n", (*it)->x, (*it)->y);


		for (int i = topLeftX + 1; i < topLeftX + width; i++)
		{
			for (int j = topLeftY + 1; j < topLeftY + height; j++)
			{
				if (!isCollisionWithAnyBrick(i, j))
				{
					brick->x = i;
					brick->y = j;
					this->bricks.push_back(brick);

					Utilss::print_log("wsadzam x:%d y:%d\n", brick->x, brick->y);
					return true;
				}
			}
		}

		return false;
	}

	bool isCollisionWithAnyBrick(int x, int y)
	{
		for(auto& b : bricks)
		{
			if (b->containsPoint(x, y))
				return true;
		}

		return false;
	}

	bool isInArea(const int x, const int y) const
	{
		return (x > topLeftX && x < topLeftX + width) &&
			(y > topLeftY && y < topLeftY + height);
	}
};
