#include "BBox.hpp"

using namespace Geometry;

Geometry::BBox::BBox() :
	topLeft(0.0f, 0.0f),
	diagonal(0.0f, 0.0f)
{
}

BBox::BBox(const Point& startPoint) :
	topLeft(startPoint),
	diagonal(0.0f, 0.0f)
{
	
}

void BBox::setStartPoint(const Point & startPoint)
{
	topLeft = startPoint;
}

void BBox::expand(const Point& point)
{
	if (point.getX() < topLeft.getX()) {
		topLeft.setX(point.getX());
	}
	else if (point.getX() > getRight()) {
		diagonal.setX(point.getX() - topLeft.getX());
	}
	
	if (point.getY() < topLeft.getY()) {
		topLeft.setY(point.getY());
	}
	else if (point.getY() > getBottom()) {
		diagonal.setY(point.getY() - topLeft.getY());
	}
}

Point BBox::getTopLeft() const
{
	return topLeft;
}

Point BBox::getTopRight() const
{
	return Point(topLeft.getX() + diagonal.getX(), topLeft.getY());
}

Point BBox::getBottomLeft() const
{
	return Point(topLeft.getX(), topLeft.getY() + diagonal.getY());
}

Point BBox::getBottomRight() const
{
	return Point(topLeft.getX() + diagonal.getX(), topLeft.getY() + diagonal.getY());
}

float BBox::getTop() const
{
	return topLeft.getY();
}

float BBox::getBottom() const
{
	return topLeft.getY() + diagonal.getY();
}

float BBox::getLeft() const
{
	return topLeft.getX();
}

float BBox::getRight() const
{
	return topLeft.getX() + diagonal.getX();
}

Point BBox::getCenter() const
{
	return topLeft + (diagonal/2.0f);
}

bool BBox::contains(const Point& point) const
{
	if (point.getX() < getLeft() ||
		point.getX() > getRight() ||
		point.getY() > getBottom() ||
		point.getY() < getTop()) {

		return false;
	}
	return true;
}
