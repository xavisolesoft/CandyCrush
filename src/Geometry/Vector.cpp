#include "Vector.hpp"

using namespace Geometry;

Vector::Vector(float x, float y)
{
	vector.x = x;
	vector.y = y;
}

Vector::Vector(const Vector & other)
{
	vector = other.vector;
}

float Vector::getX() const
{
	return vector.x;
}

float Vector::getY() const
{
	return vector.y;
}

void Vector::setX(float value)
{
	vector.x = value;
}

void Vector::setY(float value)
{
	vector.y = value;
}
