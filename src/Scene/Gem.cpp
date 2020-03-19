#include "Gem.hpp"

#include "../Animation/Animation.hpp"

using namespace Scene;
using namespace Geometry;
using namespace Animation;

Gem::Gem(long id, GemType gemType) :
	id(id),
	gemType(gemType),
	animation(nullptr)
{

}

long Gem::getId() const
{
	return id;
}

GemType Gem::getGemType() const
{
	return gemType;
}

void Gem::setWorldPos(const Point & point)
{
	worldPos = point;
}

void Gem::setX(float x)
{
	worldPos.setX(x);
}

void Gem::setY(float y)
{
	worldPos.setY(y);
}

const Point& Gem::getWorldPos() const
{
	return worldPos;
}

void Gem::setAnimation(Animation::IAnimation& value)
{
	animation = &value;
}

IAnimation* Gem::getAnimation() const
{
	return animation;
}

void Gem::animationUpdate()
{
	//TODO: When create a GameObject superClass move animated related functions there.
	if (animation) {
		if (animation->update()) {
			delete animation;
			animation = nullptr;
		}
	}
}

bool Gem::isUserInteractionEnabled() const
{
	return !animation;
}
