#include "MoveGemAnimation.hpp"

#include "../GemObject/Gem.hpp"

using namespace Animation;
using namespace Geometry;
using namespace GemObject;

MoveGemAnimation::MoveGemAnimation() :
	lastUpdate(0)
{

}

Animation::MoveGemAnimation::~MoveGemAnimation()
{
}

void MoveGemAnimation::start(std::shared_ptr<Gem> gem, const Point& source, const Point& destination, int steps, float perideSeconds)
{
	this->gem = gem;
	this->source = source;
	this->move = destination - source;
	TOTAL_STEPS = steps;
	PERIODE_SECONDS = perideSeconds;
	lastUpdate = 0;

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
