#pragma once

#include <memory>
#include <ctime>

#include "IAnimation.hpp"
#include "../Geometry/Point.hpp"

namespace GemObject
{
	class Gem;
}

namespace Animation {
	class MoveGemAnimation :
		public IAnimation
	{
	public:
		MoveGemAnimation();
		~MoveGemAnimation();
		
		void start(std::shared_ptr<GemObject::Gem> gem, const Geometry::Point& source, const Geometry::Point& destination, int steps, float perideSeconds);

		bool update() override;

	private:
		std::shared_ptr<GemObject::Gem> gem;
		Geometry::Point source;
		Geometry::Vector move;
		std::clock_t lastUpdate;

		int TOTAL_STEPS;
		float PERIODE_SECONDS;
		int currentStep;
	};
}
