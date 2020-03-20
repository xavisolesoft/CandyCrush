#include "GemGenerator.hpp"

#include <king/Engine.h>

#include <cstdlib>

#include "../Render/RenderController.hpp"
#include "../Gem/GemRenderer.hpp"
#include "../Gem/GemGenerator.hpp"

using namespace Gem;

GemGenerator::GemGenerator(Render::RenderController& renderController) :
	nextGemId(0),
	renderController(renderController)
{
	std::srand(60);
}

std::shared_ptr<GemObject> GemGenerator::createNextGem()
{
	auto gem = std::shared_ptr<GemObject>(new GemObject(genereateNextId(),
														generateNextGemType()),
										[this](GemObject* gem) {
											renderController.remove(*gem);
										});

	renderController.add(*gem, gemRenderer);

	return gem;

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

