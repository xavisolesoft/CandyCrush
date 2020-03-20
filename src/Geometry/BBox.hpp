#pragma once

#include "Point.hpp"
#include "Vector.hpp"

namespace Geometry {
	class BBox
	{
	public:
		BBox();
		BBox(const Point<float>& startPoint);

		void setStartPoint(const Point<float>& startPoint);
		void expand(const Point<float>& point);

		Point<float> getTopLeft() const;
		Point<float> getTopRight() const;
		Point<float> getBottomLeft() const;
		Point<float> getBottomRight() const;

		float getTop() const;
		float getBottom() const;
		float getLeft() const;
		float getRight() const;

		Point<float> getCenter() const;

		bool contains(const Point<float>& point) const;

	private:
		Point<float> topLeft;
		Vector diagonal;
	};
}
