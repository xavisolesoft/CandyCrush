#include "GemGenerator.hpp"

using namespace Scene;
using namespace Geometry;

GemGenerator::GemGenerator() :
	nextGemId(0)
{
	std::srand(60);
}

std::shared_ptr<Gem> GemGenerator::createNextGem()
{
	return std::make_shared<Gem>(genereateNextId(),
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

