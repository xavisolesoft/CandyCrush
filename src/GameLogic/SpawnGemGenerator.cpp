#include "SpawnGemGenerator.hpp"

#include "../Scene/GameBoard.hpp"

#include "../Gem/GemGenerator.hpp"

using namespace GameLogic;
using namespace Scene;
using namespace Gem;

const double SpawnGemGenerator::SPAWN_PERIODE_SECS = 0.1;

SpawnGemGenerator::SpawnGemGenerator() :
	lastUpdate(0)
{
}

void SpawnGemGenerator::update(GameBoard& gameBoard, GemGenerator& gemGenerator)
{
	if ((std::clock() - lastUpdate) / (double)CLOCKS_PER_SEC >= SPAWN_PERIODE_SECS) {
		for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
			auto gem = gameBoard.getGemFromCell(i, 0);
			if (!gem) {
				gameBoard.setGemToCell(i, 0, gemGenerator.createNextGem());
			}
		}

		lastUpdate = std::clock();
	}
}