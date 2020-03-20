#pragma once

#include "Point.hpp"
#include "Vector.hpp"

namespace Geometry {
	template<class T>
	class BBox
	{
	public:
		BBox() :
			topLeft(0, 0),
			diagonal(0, 0)
		{
		}

		BBox(const Point<T>& startPoint) :
			topLeft(startPoint),
			diagonal(0, 0)
		{

		}

		void setStartPoint(const Point<T>& startPoint)
		{
			topLeft = startPoint;
		}

		void expand(const Point<T>& point)
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

		Point<T> getTopLeft() const
		{
			return topLeft;
		}

		Point<T> getTopRight() const
		{
			return Point<T>(topLeft.getX() + diagonal.getX(), topLeft.getY());
		}

		Point<T> getBottomLeft() const
		{
			return Point<T>(topLeft.getX(), topLeft.getY() + diagonal.getY());
		}

		Point<T> getBottomRight() const
		{
			return Point<T>(topLeft.getX() + diagonal.getX(), topLeft.getY() + diagonal.getY());
		}

		float getTop() const
		{
			return topLeft.getY();
		}

		float getBottom() const
		{
			return topLeft.getY() + diagonal.getY();
		}

		float getLeft() const
		{
			return topLeft.getX();
		}

		float getRight() const
		{
			return topLeft.getX() + diagonal.getX();
		}

		Point<T> getCenter() const
		{
			return topLeft + (diagonal / 2.0f);
		}

		bool contains(const Point<T>& point) const
		{
			if (point.getX() < getLeft() ||
				point.getX() > getRight() ||
				point.getY() > getBottom() ||
				point.getY() < getTop()) {

				return false;
			}
			return true;
		}

	private:
		Point<T> topLeft;
		Vector<T> diagonal;
	};
}
