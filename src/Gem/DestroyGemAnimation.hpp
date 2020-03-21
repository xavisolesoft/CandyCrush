#pragma once

#include <memory>
#include <ctime>
#include <functional>

#include "../Animation/IAnimation.hpp"
#include "../Geometry/Point.hpp"

namespace Gem
{
	class GemObject;
}

namespace Gem {
	class DestroyGemAnimation :
		public Animation::IAnimation
	{
	public:
		DestroyGemAnimation();
		~DestroyGemAnimation();

		void setGem(std::shared_ptr<Gem::GemObject> gem, std::function<void()> animationEndFunction);
		
		bool update() override;

	private:
		std::shared_ptr<Gem::GemObject> gem;

		std::clock_t lastUpdate;
		static const int TOTAL_STEPS;
		static const float PERIODE_SECONDS;
		int currentStep;
		std::function<void()> animationEndFunction;
	};
}
