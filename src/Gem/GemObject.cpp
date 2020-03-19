#include "GemObject.hpp"

using namespace Gem;

GemObject::GemObject(long id, GemType gemType) :
	gemType(gemType)
{

}

GemType GemObject::getGemType() const
{
	return gemType;
}
