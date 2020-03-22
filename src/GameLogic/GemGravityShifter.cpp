#include "GemGravityShifter.hpp"

#include "GameBoard/Board.hpp"

#include "Gem/GemObject.hpp"
#include "Gem/MoveGemAnimation.hpp"

#include "Geometry/Point.hpp"

#include "Animation/ComposedSequentialAnimation.hpp"

using namespace GameLogic;
using namespace GameBoard;
using namespace Geometry;
using namespace Animation;
using namespace Gem;

const float GemGravityShifter::BOUNCE_LENGTH = 5;
const float GemGravityShifter::BOUNCE_SPEED = 80.0f;

const float GemGravityShifter::GRAVITY_SPEED = 200.0f;

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
				auto gravityAnimation = new MoveGemAnimation();
				Point<float> destination = gameBoard.getWorldPosFromCell(i, j);
				Point<float> origin = gameBoard.getWorldPosFromCell(i, j - 1);
				gravityAnimation->start(upperGem, origin, destination, GRAVITY_SPEED);
				gravityAnimation->setStepEndFunction([&gameBoard, upperGem, destination, i, j]() {
														auto gemBottomGem = gameBoard.getGemFromCell(i, j + 1);
														if ((j >= gameBoard.getNumYCells() - 1) || (gemBottomGem && gemBottomGem->isUserInteractionEnabled())) {
															auto composedAnimation = dynamic_cast<ComposedSequentialAnimation*>(upperGem->getAnimation());
															Point<float> bounceTop(destination.getX(), destination.getY() - BOUNCE_LENGTH);
															auto bounceAnimation = new MoveGemAnimation();
															bounceAnimation->start(upperGem, destination, bounceTop, BOUNCE_SPEED);
															composedAnimation->appendAnimation(*bounceAnimation);
															auto bounceReturnAnimation = new MoveGemAnimation();
															bounceReturnAnimation->start(upperGem, bounceTop, destination, BOUNCE_SPEED);
															composedAnimation->appendAnimation(*bounceReturnAnimation);
														}
													});
				auto composedAnimation = new ComposedSequentialAnimation();
				composedAnimation->appendAnimation(*gravityAnimation);
				upperGem->setAnimation(*composedAnimation);

				gameBoard.setGemToCell(i, j, upperGem);
				gameBoard.setGemToCell(i, j - 1, nullptr);
			}
		}
	}
}
