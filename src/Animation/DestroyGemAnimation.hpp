#pragma once

#include <memory>
#include <ctime>
#include <functional>

#include "Animation.hpp"
#include "../Geometry/Point.hpp"

namespace Scene
{
	class Gem;
}

namespace Animation {
	class DestroyGemAnimation :
		public IAnimation
	{
	public:
		DestroyGemAnimation();
		~DestroyGemAnimation();

		void setGem(std::shared_ptr<Scene::Gem> gem, std::function<void()> animationEndFunction);
		
		bool update() override;

	private:
		std::shared_ptr<Scene::Gem> gem;

		std::clock_t lastUpdate;
		static const int TOTAL_STEPS;
		static const float PERIODE_SECONDS;
		int currentStep;
		std::function<void()> animationEndFunction;
	};
}
