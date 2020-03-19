#include "GemGenerator.hpp"

#include <cstdlib>

using namespace Gem;

GemGenerator::GemGenerator() :
	nextGemId(0)
{
	std::srand(60);
}

std::shared_ptr<GemObject> GemGenerator::createNextGem()
{
	return std::make_shared<GemObject>(genereateNextId(),
								 generateNextGemType());
}

long GemGenerator::genereateNextId()
{
	return nextGemId++;
}

GemType GemGenerator::generateNextGemType() const
{
	int random = std::rand() % 5;
	switch (random)
	{
	case 0:
		return GemType::BLUE;
	case 1:
		return GemType::GREEN;
	case 2:
		return GemType::PURPLE;
	case 3:
		return GemType::RED;
	default:
		return GemType::YELLOW;
	}
}

