#include "GemGenerator.hpp"

#include <king/Engine.h>

#include <cstdlib>

#include "../Render/RenderController.hpp"
#include "../Gem/GemRenderer.hpp"
#include "../Gem/GemGenerator.hpp"

#include "../Util/Debug.hpp"

using namespace Gem;
using namespace Util;

GemGenerator::GemGenerator(Render::RenderController& renderController) :
	nextGemId(0),
	renderController(renderController)
{
	std::srand(60);
}

std::shared_ptr<GemObject> GemGenerator::createNextGem()
{
	/*
	 * Note: The design is prepared for future optimizations like static object pool.
	 *		 But for now is not needed because we don't have performance issues due the small
	 *       number of gems created by the game.
	 */
	auto gem = std::shared_ptr<GemObject>(new GemObject(genereateNextId(),
														generateNextGemType()),
										[this](GemObject* gem) {
											renderController.remove(*gem);
											Debug() << "DELETED_GEM(" << gem->getId() << ", " << (int)gem->getGemType() << ")";
										});

	renderController.add(*gem, *new GemRenderer());

	Debug() << "NEW_GEM(" << gem->getId() << ", " << (int)gem->getGemType() << ")";

	return gem;

}

void GemGenerator::setSeed(unsigned value)
{
	std::srand(value);
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

