#pragma once

#include "Vector.hpp"

namespace Geometry {
	class Point
	{
	public:
		Point(float x = 0, float y = 0);

		float getX() const;
		float getY() const;

		void setX(float value);
		void setY(float value);

		bool operator==(const Point& other) const
		{
			return x == other.x && y == other.y;
		}

		Point& operator+=(const Vector& vector)
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}

		Point operator+(const Vector& vector) const
		{
			Point ret(*this);
			ret.x += vector.x;
			ret.y += vector.y;
			return ret;
		}

		Vector operator-(const Point& other) const
		{
			Vector ret;
			ret.x = x - other.x;
			ret.y = y - other.y;
			return ret;
		}

	private:
		float x;
		float y;
	};
}
