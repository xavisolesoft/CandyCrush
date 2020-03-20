#pragma once

#include "PointF.hpp"
#include "Vector.hpp"

namespace Geometry {
	class BBox
	{
	public:
		BBox();
		BBox(const PointF& startPoint);

		void setStartPoint(const PointF& startPoint);
		void expand(const PointF& point);

		PointF getTopLeft() const;
		PointF getTopRight() const;
		PointF getBottomLeft() const;
		PointF getBottomRight() const;

		float getTop() const;
		float getBottom() const;
		float getLeft() const;
		float getRight() const;

		PointF getCenter() const;

		bool contains(const PointF& point) const;

	private:
		PointF topLeft;
		Vector diagonal;
	};
}
