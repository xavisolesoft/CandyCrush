#pragma once

#include "../Geometry/BBox.hpp"
#include "../Geometry/Point.hpp"

namespace Animation
{
	class IAnimation;
}

namespace GameObject {
	class IGameObject
	{
	public:
		IGameObject(long id);
		virtual ~IGameObject();
		
		long getId() const;

		void setWorldPos(const Geometry::Point& point);
		void setWorldX(float x);
		void setWorldY(float y);
		const Geometry::Point& getWorldPos() const;

		float getRotation() const;
		void setRotation(float value);

		float getScale() const;
		void setScale(float value);

		void setAnimation(Animation::IAnimation& value);
		Animation::IAnimation* getAnimation() const;
		void animationUpdate();

		bool isUserInteractionEnabled() const;

	protected:
		long id;
		Geometry::Point worldPos;
		float rotation;
		float scale;
		Animation::IAnimation* animation;
	};
}
