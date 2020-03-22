#pragma once

#include "Vector.hpp"

namespace Geometry {
	template<class T>
	class Point
	{
	public:
		Point(T x = 0, T y = 0)
		{
			this->x = x;
			this->y = y;
		}

		T getX() const
		{
			return x;
		}

		T getY() const
		{
			return y;
		}

		void setX(T value)
		{
			x = value;
		}

		void setY(T value)
		{
			y = value;
		}

		bool operator==(const Point<T>& other) const
		{
			return x == other.x && y == other.y;
		}

		Point<T>& operator+=(const Vector<T>& vector)
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}

		Point<T> operator+(const Point<T>& vector) const
		{
			Point<T> ret(*this);
			ret.x += vector.x;
			ret.y += vector.y;
			return ret;
		}

		Point<T> operator+(const Vector<T>& vector) const
		{
			Point<T> ret(*this);
			ret.x += vector.x;
			ret.y += vector.y;
			return ret;
		}

		Vector<T> operator-(const Point<T>& other) const
		{
			Vector<T> ret;
			ret.x = x - other.x;
			ret.y = y - other.y;
			return ret;
		}

	private:
		T x;
		T y;
	};
}
