#pragma once

#define BRICK_HEIGHT 3
#define BRICK_WIDTH 5

class Brick
{

public:
	int x, y;
	int width, height;

	int colorPair;

	Brick(const int x, const int y);

	bool containsPoint(const int x, const int y) const;
};


