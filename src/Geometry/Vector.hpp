#pragma once

namespace Geometry {
	class Vector
	{
		friend class PointF;

	public:
		Vector(float x = 0.0f, float y = 0.0f);
		Vector(const Vector& other);

		float getX() const;
		float getY() const;

		void setX(float value);
		void setY(float value);

		bool operator==(const Vector& other) const
		{
			return x == other.x && y == other.y;
		}

		Vector& operator/=(float literal)
		{
			x /= literal;
			y /= literal;
			return *this;
		}

		Vector operator/(float literal) const
		{
			Vector ret(*this);
			ret.x /= literal;
			ret.y /= literal;
			return ret;
		}

		Vector operator*(float literal) const
		{
			Vector ret(*this);
			ret.x *= literal;
			ret.y *= literal;
			return ret;
		}

	private:
		float x;
		float y;
	};
}
