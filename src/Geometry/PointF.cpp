#include "PointF.hpp"

using namespace Geometry;

PointF::PointF(float x, float y)
{
	this->x = x;
	this->y = y;
}

float PointF::getX() const
{
	return x;
}

float PointF::getY() const
{
	return y;
}

void PointF::setX(float value)
{
	x = value;
}

void PointF::setY(float value)
{
	y = value;
}
