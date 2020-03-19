#include "Gem.hpp"

using namespace GemObject;

Gem::Gem(long id, GemType gemType) :
	gemType(gemType)
{

}

GemType Gem::getGemType() const
{
	return gemType;
}
