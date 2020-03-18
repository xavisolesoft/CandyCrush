#include "Gem.hpp"

using namespace Scene;
using namespace Geometry;

Gem::Gem(long id, GemType gemType) :
	id(id),
	gemType(gemType)
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

const Point & Gem::getWorldPos() const
{
	return worldPos;
}
