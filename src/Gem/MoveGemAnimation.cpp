#include "MoveGemAnimation.hpp"

#include "Gem/GemObject.hpp"

using namespace Animation;
using namespace Geometry;
using namespace Gem;

MoveGemAnimation::MoveGemAnimation() :
	lastUpdate(0)
{

}

MoveGemAnimation::~MoveGemAnimation()
{
}

void MoveGemAnimation::setStepTriggeredFunction(float distanceTrigger, std::function<void()> animationStepFunction)
{
	this->distanceTrigger = distanceTrigger;
	this->animationStepFunction = animationStepFunction;
}

void MoveGemAnimation::setStepEndFunction(std::function<void()> animationEndFunction)
{
	this->animationEndFunction = animationEndFunction;
}

void MoveGemAnimation::start(std::shared_ptr<GemObject> gem, const Point<float>& origin, const Point<float>& destination, float speed)
{
	this->gem = gem;
	this->origin = origin;
	this->destination = destination;
	this->move = destination - origin;
	this->speed = speed;
	this->lastUpdate = 0;
}

bool MoveGemAnimation::update()
{
	if (lastUpdate == 0) {
		lastUpdate = std::clock();
	}

	bool finished = false;
	float stepDuration = (std::clock() - lastUpdate)/(float)CLOCKS_PER_SEC;
	float stepDistance = speed*stepDuration;
	Vector<float> toEndMoveVector = destination - gem->getWorldPos();
	float distanceToDestination = toEndMoveVector.norm();
	
	if (distanceToDestination > stepDistance) {
		Vector<float> stepMoveVector = move.normalized()*stepDistance;
		gem->setWorldPos(gem->getWorldPos() + stepMoveVector);
	}
	else {
		gem->setWorldPos(destination);
		finished = true;
		lastUpdate = 0;
	}

	float distanceFromOrigin = Vector<float>(gem->getWorldPos() - origin).norm();
	if (animationStepFunction && distanceFromOrigin > distanceTrigger) {
		animationStepFunction();
		animationStepFunction == nullptr;
	}

	if (finished && animationEndFunction) {
		animationEndFunction();
	}
	
	lastUpdate = std::clock();

	return finished;
}

