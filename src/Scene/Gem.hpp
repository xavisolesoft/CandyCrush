#pragma once

#include "../Geometry/BBox.hpp"
#include "../Geometry/Point.hpp"

namespace Scene {
	enum class GemType
	{
		UNDEFINED,
		BLUE,
		GREEN,
		PURPLE,
		RED,
		YELLOW
	};

	class Gem
	{
	public:
		Gem(long id, GemType gemType);

		long getId() const;
		GemType getGemType() const;

		void setWorldPos(const Geometry::Point& point);
		void setX(float x);
		void setY(float y);
		const Geometry::Point& getWorldPos() const;

	private:
		long id;
		GemType gemType;
		Geometry::Point worldPos;
	};
}
