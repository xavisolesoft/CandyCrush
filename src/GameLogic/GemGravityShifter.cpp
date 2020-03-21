#include "GemGravityShifter.hpp"

#include "../GameBoard/Board.hpp"

#include "../Gem/GemObject.hpp"
#include "../Gem/MoveGemAnimation.hpp"

#include "../Geometry/Point.hpp"

using namespace GameLogic;
using namespace GameBoard;
using namespace Geometry;
using namespace Gem;

GemGravityShifter::GemGravityShifter()
{
}

void GemGravityShifter::update(Board& gameBoard)
{
	for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
		for (int j = gameBoard.getNumYCells() - 1; j > 0; --j) {
			auto gem = gameBoard.getGemFromCell(i, j);
			auto upperGem = gameBoard.getGemFromCell(i, j - 1);
			if (!gem && upperGem && upperGem->isUserInteractionEnabled()) {
				auto animation1 = new MoveGemAnimation();
				Point<float> destination = gameBoard.getWorldPosFromCell(i, j);
				Point<float> origin = gameBoard.getWorldPosFromCell(i, j - 1);
				animation1->start(upperGem, origin, destination, 10, 0.01f);
				upperGem->setAnimation(*animation1);
				gameBoard.swap(i, j, i, j - 1);
			}
		}
	}
}
