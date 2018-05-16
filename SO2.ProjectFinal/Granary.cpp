#include "stdafx.h"
#include "Granary.h"


Granary::Granary()
{
}


Granary::~Granary()
{
}

void Granary::add_wood(Wood wood)
{
	mx.lock();

	woods.push_back(wood);
	cv_woods.notify_one();

	mx.unlock();
}

Wood Granary::take_one_wood()
{
	mx.lock();

	const auto w = woods.front();
	cv_woods.notify_one();

	mx.unlock();

	return w;
}
