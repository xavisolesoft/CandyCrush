#pragma once

#include "../Geometry/BBox.hpp"
#include "../Geometry/PointF.hpp"

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

		void setWorldPos(const Geometry::PointF& point);
		void setWorldX(float x);
		void setWorldY(float y);
		const Geometry::PointF& getWorldPos() const;

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
		Geometry::PointF worldPos;
		float rotation;
		float scale;
		Animation::IAnimation* animation;
	};
}
