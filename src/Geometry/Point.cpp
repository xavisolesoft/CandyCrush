#include "Point.hpp"

using namespace Geometry;

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Point::getX() const
{
	return x;
}

float Point::getY() const
{
	return y;
}

void Point::setX(float value)
{
	x = value;
}

void Point::setY(float value)
{
	y = value;
}
