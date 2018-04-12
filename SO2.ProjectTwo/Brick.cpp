#include "stdafx.h"
#include "Brick.h"
#include "Utilss.h"


Brick::Brick(const int x, const int y)
{
	this->x = x;
	this->y = y;

	this->width = BRICK_WIDTH;
	this->height = BRICK_HEIGHT;

	this->colorPair = Utilss::random_in_range(1, 49);
}

bool Brick::containsPoint(const int x, const int y) const
{
	return (x >= this->x && x <= this->x + width) &&
		(y >= this->y && y <= this->y + height);
}

