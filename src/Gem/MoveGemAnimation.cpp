#include "MoveGemAnimation.hpp"

#include "../Gem/GemObject.hpp"

using namespace Animation;
using namespace Geometry;
using namespace Gem;

MoveGemAnimation::MoveGemAnimation() :
	lastUpdate(0),
	stepFunctionTrigger(-1)
{

}

MoveGemAnimation::~MoveGemAnimation()
{
}

void MoveGemAnimation::setStepTriggeredFunction(int stepNumber, std::function<void()> animationEndFunction)
{
	stepFunctionTrigger = stepNumber;
	this->animationEndFunction = animationEndFunction;
}

void MoveGemAnimation::start(std::shared_ptr<GemObject> gem, const Point<float>& origin, const Point<float>& destination, int steps, float perideSeconds)
{
	this->gem = gem;
	this->origin = origin;
	this->move = destination - origin;
	TOTAL_STEPS = steps;
	PERIODE_SECONDS = perideSeconds;
	lastUpdate = 0;

	currentStep = 0;
}

bool MoveGemAnimation::update()
{
	if (currentStep < TOTAL_STEPS && (std::clock() - lastUpdate) / (double)CLOCKS_PER_SEC >= PERIODE_SECONDS) {
		++currentStep;
		gem->setWorldPos(origin + (move/(float)TOTAL_STEPS)*(float)currentStep);
		
		lastUpdate = std::clock();
	}

	bool end = currentStep >= TOTAL_STEPS;
	if (currentStep == stepFunctionTrigger && animationEndFunction) {
		animationEndFunction();
	}

	return end;
}
