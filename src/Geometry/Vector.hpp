#pragma once

namespace Geometry {
	template<class T>
	class Vector
	{
		template<class T>
		friend class Point;

	public:
		Vector(T x = 0, T y = 0)
		{
			this->x = x;
			this->y = y;
		}

		Vector(const Vector<T> & other)
		{
			x = other.x;
			y = other.y;
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

		bool operator==(const Vector<T>& other) const
		{
			return x == other.x && y == other.y;
		}

		Vector<T>& operator/=(T literal)
		{
			x /= literal;
			y /= literal;
			return *this;
		}

		Vector<T> operator/(T literal) const
		{
			Vector<T> ret(*this);
			ret.x /= literal;
			ret.y /= literal;
			return ret;
		}

		Vector<T> operator*(T literal) const
		{
			Vector<T> ret(*this);
			ret.x *= literal;
			ret.y *= literal;
			return ret;
		}

	private:
		T x;
		T y;
	};
}
