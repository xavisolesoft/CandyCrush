#pragma once

#include <functional>
#include <memory>
#include <ctime>

#include "Animation/IAnimation.hpp"
#include "Geometry/Point.hpp"

namespace Gem {
	class GemObject;

	class MoveGemAnimation :
		public Animation::IAnimation
	{
	public:
		MoveGemAnimation();
		~MoveGemAnimation();
		
		void setStepTriggeredFunction(float distanceTrigger, std::function<void()> animationStepFunction);
		void setStepEndFunction(std::function<void()> animationEndFunction);

		void start(std::shared_ptr<Gem::GemObject> gem, const Geometry::Point<float>& origin, const Geometry::Point<float>& destination, float speed);

		bool update() override;

	private:
		std::shared_ptr<Gem::GemObject> gem;
		Geometry::Point<float> origin;
		Geometry::Point<float> destination;
		Geometry::Vector<float> move;
		std::clock_t lastUpdate;

		float speed;
		float distanceTrigger;

		std::function<void()> animationStepFunction;
		std::function<void()> animationEndFunction;
	};
}
