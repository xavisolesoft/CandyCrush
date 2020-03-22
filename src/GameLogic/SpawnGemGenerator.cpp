#include "SpawnGemGenerator.hpp"

#include "GameBoard/Board.hpp"

#include "Gem/GemGenerator.hpp"

using namespace GameLogic;
using namespace GameBoard;
using namespace Gem;

SpawnGemGenerator::SpawnGemGenerator()
{
}

void SpawnGemGenerator::update(Board& gameBoard, GemGenerator& gemGenerator)
{
	for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
		auto gem = gameBoard.getGemFromCell(i, 0);
		auto gemBottom = gameBoard.getGemFromCell(i, 1);
		if (!gem && (!gemBottom || !gameBoard.getCellBBox(i, 0).contains(gemBottom->getWorldPos()))) {
			gameBoard.setGemToCell(i, 0, gemGenerator.createNextGem());
		}
	}
}
