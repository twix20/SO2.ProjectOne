#pragma once

class Brick
{

public:
	int x, y;
	int width, height;

	Brick(const int x, const int y)
	{
		this->x = x;
		this->y = y;

		this->width = 2;
		this->height = 2;
	}

	bool containsPoint(const int x, const int y) const
	{
		return (x >= this->x && x <= this->x + width) &&
			   (y >= this->y && y <= this->y + height);
	}
};


