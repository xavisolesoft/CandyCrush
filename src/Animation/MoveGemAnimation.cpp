#include "MoveGemAnimation.hpp"

#include "../Scene/Gem.hpp"
#include "../Geometry/Point.hpp"

using namespace Animation;
using namespace Geometry;
using namespace Scene;

MoveGemAnimation::MoveGemAnimation()
{

}

Animation::MoveGemAnimation::~MoveGemAnimation()
{
}

void MoveGemAnimation::start(std::shared_ptr<Gem> gem, const Point& dest, int steps, float perideSeconds)
{
	this->gem = gem;
	source = gem->getWorldPos();
	this->move = dest - source;
	TOTAL_STEPS = steps;
	PERIODE_SECONDS = perideSeconds;

	currentStep = 0;
}

bool MoveGemAnimation::update()
{
	if (currentStep < TOTAL_STEPS && (std::clock() - lastUpdate) / (double)CLOCKS_PER_SEC >= PERIODE_SECONDS) {
		++currentStep;
		gem->setWorldPos(source + (move/(float)TOTAL_STEPS)*(float)currentStep);
		
		lastUpdate = std::clock();
	}

	return currentStep >= TOTAL_STEPS;
}
