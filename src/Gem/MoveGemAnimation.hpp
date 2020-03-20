#pragma once

#include <memory>
#include <ctime>

#include "../Animation/IAnimation.hpp"
#include "../Geometry/PointF.hpp"

namespace Gem
{
	class GemObject;
}

namespace Animation {
	class MoveGemAnimation :
		public IAnimation
	{
	public:
		MoveGemAnimation();
		~MoveGemAnimation();
		
		void start(std::shared_ptr<Gem::GemObject> gem, const Geometry::PointF& source, const Geometry::PointF& destination, int steps, float perideSeconds);

		bool update() override;

	private:
		std::shared_ptr<Gem::GemObject> gem;
		Geometry::PointF source;
		Geometry::Vector move;
		std::clock_t lastUpdate;

		int TOTAL_STEPS;
		float PERIODE_SECONDS;
		int currentStep;
	};
}
