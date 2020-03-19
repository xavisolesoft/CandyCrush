#pragma once

#include <glm/vec2.hpp>

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
			return point == other.point;
		}

		Point& operator+=(const Vector& vector)
		{
			point += vector.vector;
			return *this;
		}

		Point operator+(const Vector& vector) const
		{
			Point ret(*this);
			ret.point += vector.vector;
			return ret;
		}

		Vector operator-(const Point& other) const
		{
			Vector ret;
			ret.vector = point - other.point;
			return ret;
		}

	private:
		glm::vec2 point;
	};
}
