#include "ComposedSequentialAnimation.hpp"

using namespace Animation;

ComposedSequentialAnimation::ComposedSequentialAnimation()
{

}

ComposedSequentialAnimation::~ComposedSequentialAnimation()
{
}

void ComposedSequentialAnimation::appendAnimation(IAnimation& animation)
{
	animations.push_back(&animation);
}

bool ComposedSequentialAnimation::update()
{
	if (animations.empty()) {
		return true;
	}

	if (animations.front()->update()) {
		auto finishedAnimation = animations.front();
		animations.pop_front();
		delete finishedAnimation;
	}

	return animations.empty();
}
