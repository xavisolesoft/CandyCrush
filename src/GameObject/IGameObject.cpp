#include "IGameObject.hpp"

#include "../Animation/IAnimation.hpp"

using namespace GameObject;
using namespace Geometry;
using namespace Animation;

IGameObject::IGameObject(long id) :
	id(id),
	rotation(0.0f),
	scale(1.0f),
	animation(nullptr)
{
	
}

IGameObject::~IGameObject()
{
	
}

long IGameObject::getId() const
{
	return id;
}

void IGameObject::setWorldPos(const Point<float>& point)
{
	worldPos = point;
}

void IGameObject::setWorldX(float x)
{
	worldPos.setX(x);
}

void IGameObject::setWorldY(float y)
{
	worldPos.setY(y);
}

const Point<float>& IGameObject::getWorldPos() const
{
	return worldPos;
}

float IGameObject::getRotation() const
{
	return rotation;
}

void IGameObject::setRotation(float value)
{
	rotation = value;
}

float IGameObject::getScale() const
{
	return scale;
}

void IGameObject::setScale(float value)
{
	scale = value;
}

void IGameObject::setAnimation(Animation::IAnimation& value)
{
	animation = &value;
}

IAnimation* IGameObject::getAnimation() const
{
	return animation;
}

void IGameObject::animationUpdate()
{
	if (animation) {
		if (animation->update()) {
			delete animation;
			animation = nullptr;
		}
	}
}

bool IGameObject::isUserInteractionEnabled() const
{
	return !animation;
}
