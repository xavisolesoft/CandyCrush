#pragma once

#include <glm/vec2.hpp>

namespace Geometry {
	class Vector
	{
		friend class Point;

	public:
		Vector(float x = 0.0f, float y = 0.0f);
		Vector(const Vector& other);

		float getX() const;
		float getY() const;

		void setX(float value);
		void setY(float value);

		bool operator==(const Vector& other) const
		{
			return vector == other.vector;
		}

		Vector& operator/=(float literal)
		{
			vector /= literal;
			return *this;
		}

		Vector operator/(float literal) const
		{
			Vector ret(*this);
			ret.vector /= literal;
			return ret;
		}

		Vector operator*(float literal) const
		{
			Vector ret(*this);
			ret.vector *= literal;
			return ret;
		}

	private:
		glm::vec2 vector;
	};
}
