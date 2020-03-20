#include "GemGravityShifter.hpp"

#include "../Scene/GameBoard.hpp"

using namespace GameLogic;
using namespace Scene;
using namespace Gem;

const double GemGravityShifter::SHIFT_PERIODE_SECS = 0.1;

GemGravityShifter::GemGravityShifter() :
	lastUpdate(0)
{
}

void GemGravityShifter::update(GameBoard& gameBoard)
{
	if ((std::clock() - lastUpdate) / (double)CLOCKS_PER_SEC >= SHIFT_PERIODE_SECS) {
		for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
			for (int j = gameBoard.getNumYCells() - 1; j > 0; --j) {
				auto gem = gameBoard.getGemFromCell(i, j);
				if (!gem) {
					gameBoard.swap(i, j, i, j - 1);
				}
			}
		}

		lastUpdate = std::clock();
	}
}
