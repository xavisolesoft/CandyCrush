#include "DestroyGemAnimation.hpp"

#include "../GemObject/Gem.hpp"

using namespace Animation;
using namespace GemObject;

const int DestroyGemAnimation::TOTAL_STEPS = 30;
const float DestroyGemAnimation::PERIODE_SECONDS = 0.01f;

DestroyGemAnimation::DestroyGemAnimation() :
	lastUpdate(0),
	currentStep(0)
{

}

DestroyGemAnimation::~DestroyGemAnimation()
{
}

void DestroyGemAnimation::setGem(std::shared_ptr<Gem> gem, std::function<void()> animationEndFunction)
{
	this->gem = gem;
	this->animationEndFunction = std::move(animationEndFunction);
}

bool DestroyGemAnimation::update()
{
	if(currentStep < TOTAL_STEPS && (std::clock() - lastUpdate) / (double)CLOCKS_PER_SEC >= PERIODE_SECONDS) {
		++currentStep;
		gem->setScale(1.0f - (1.0f/(float)TOTAL_STEPS)*(float)currentStep);

		lastUpdate = std::clock();
	}

	bool end = currentStep >= TOTAL_STEPS;
	if (end) {
		animationEndFunction();
	}

	return end;
}
