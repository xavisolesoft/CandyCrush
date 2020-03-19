#pragma once

#include "../Geometry/BBox.hpp"
#include "../Geometry/Point.hpp"

namespace Animation
{
	class IAnimation;
}

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

		void setAnimation(Animation::IAnimation& value);
		Animation::IAnimation* getAnimation() const;
		void animationUpdate();

		bool isUserInteractionEnabled() const;

	private:
		long id;
		GemType gemType;
		Geometry::Point worldPos;
		Animation::IAnimation* animation;
	};
}
