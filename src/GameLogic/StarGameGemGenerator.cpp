#include "StarGameGemGenerator.hpp"

#include "../Scene/GameBoard.hpp"

#include "../Gem/GemGenerator.hpp"

#include "../GameLogic/LineMatcher.hpp"

using namespace GameLogic;
using namespace Scene;
using namespace Gem;

StarGameGemGenerator::StarGameGemGenerator()
{
}

void StarGameGemGenerator::generateStartConfiguration(GameBoard& gameBoard, GemGenerator& gemGenerator)
{
	for (int j = 0; j < gameBoard.getNumYCells(); ++j) {
		for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
			auto gem = gemGenerator.createNextGem();
			gameBoard.setGemToCell(i, j, gem);
		}
	}

	std::vector<std::vector<Geometry::Point<int>> > lines;
	do {
		LineMatcher lineMatcher(gameBoard);
		lines = lineMatcher.getBoardLines();

		for (const std::vector<Geometry::Point<int>> line : lines) {
			for (const Geometry::Point<int>& point : line) {
				auto gem = gemGenerator.createNextGem();
				gameBoard.setGemToCell((int)point.getX(), (int)point.getY(), gem);
			}
		}
	} while (!lines.empty());
}
