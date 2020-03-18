#include "Point.hpp"

using namespace Geometry;

Point::Point(float x, float y)
{
	point.x = x;
	point.y = y;
}

float Point::getX() const
{
	return point.x;
}

float Point::getY() const
{
	return point.y;
}

void Point::setX(float value)
{
	point.x = value;
}

void Point::setY(float value)
{
	point.y = value;
}
