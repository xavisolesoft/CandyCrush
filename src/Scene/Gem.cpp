#include "Gem.hpp"

using namespace Scene;

Gem::Gem(long id, GemType gemType) :
	gemType(gemType)
{

}

GemType Gem::getGemType() const
{
	return gemType;
}
