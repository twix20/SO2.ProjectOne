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

	std::vector<std::shared_ptr<Brick>> bricks;

	//returns true if moved out of area
	bool tryMoveBrickSouth(std::shared_ptr<Brick> brick) const
	{
		if (!isInArea(brick->x, brick->y + brick->height))
		{
			return false;
		}

		brick->y++;
		return true;
	}

	bool tryEmbedBrick(std::shared_ptr<Brick> brick)
	{
		for (int i = topLeftX + 1; i < topLeftX + width; i++)
		{
			for (int j = topLeftY + 1; j < topLeftY + height; j++)
			{
				if (!isCollisionWithAnyBrick(i, j))
				{
					brick->x = i;
					brick->y = j;
					this->bricks.push_back(brick);
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
