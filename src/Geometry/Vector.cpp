#include "Vector.hpp"

using namespace Geometry;

Vector::Vector(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector::Vector(const Vector & other)
{
	x = other.x;
	y = other.y;
}

float Vector::getX() const
{
	return x;
}

float Vector::getY() const
{
	return y;
}

void Vector::setX(float value)
{
	x = value;
}

void Vector::setY(float value)
{
	y = value;
}
