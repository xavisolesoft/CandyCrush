#pragma once

#include "Point.hpp"
#include "Vector.hpp"

namespace Geometry {
	class BBox
	{
	public:
		BBox();
		BBox(const Point& startPoint);

		void setStartPoint(const Point& startPoint);
		void expand(const Point& point);

		Point getTopLeft() const;
		Point getTopRight() const;
		Point getBottomLeft() const;
		Point getBottomRight() const;

		float getTop() const;
		float getBottom() const;
		float getLeft() const;
		float getRight() const;

		Point getCenter() const;

		bool contains(const Point& point) const;

	private:
		Point topLeft;
		Vector diagonal;
	};
}
