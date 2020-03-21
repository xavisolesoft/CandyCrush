#include "GemAnimationUpdater.hpp"

#include "../Scene/Board.hpp"
#include "../Gem/GemGenerator.hpp"

using namespace GameLogic;
using namespace Scene;
using namespace Gem;

GemAnimationUpdater::GemAnimationUpdater()
{
}

void GemAnimationUpdater::update(Board& gameBoard)
{
	for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
		for (int j = 0; j < gameBoard.getNumYCells(); ++j) {
			std::shared_ptr<Gem::GemObject> gem = gameBoard.getGemFromCell(i, j);
			if (gem) {
				gem->animationUpdate();
			}
		}
	}
}
