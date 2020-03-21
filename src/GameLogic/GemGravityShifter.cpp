#include "GemGravityShifter.hpp"

#include "../GameBoard/Board.hpp"

#include "../Gem/GemObject.hpp"
#include "../Gem/MoveGemAnimation.hpp"

#include "../Geometry/Point.hpp"

#include "../Animation/ComposedSequentialAnimation.hpp"

using namespace GameLogic;
using namespace GameBoard;
using namespace Geometry;
using namespace Animation;
using namespace Gem;

const float GemGravityShifter::BOUNCE_LENGTH = 5;
const int GemGravityShifter::BOUNCE_STEPS = 4;
const float GemGravityShifter::BOUNCE_PERIOD_SECONDS = 0.01f;

const int GemGravityShifter::GRAVITY_STEPS = 10;
const float GemGravityShifter::GRAVITY_PERIOD_SECONDS = 0.01f;
const int GemGravityShifter::GRAVITY_STEP_FOR_CELL_CHANGE = 5;

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
				auto composedAnimation = new ComposedSequentialAnimation();

				auto gravityAnimation = new MoveGemAnimation();
				Point<float> destination = gameBoard.getWorldPosFromCell(i, j);
				Point<float> origin = gameBoard.getWorldPosFromCell(i, j - 1);
				gravityAnimation->start(upperGem, origin, destination, GRAVITY_STEPS, GRAVITY_PERIOD_SECONDS);
				gravityAnimation->setStepTriggeredFunction(GRAVITY_STEP_FOR_CELL_CHANGE,
													[&gameBoard, &gem, i, j]() {
														gameBoard.setGemToCell(i, j, gem);
														gameBoard.setGemToCell(i, j - 1, nullptr);
													});
				composedAnimation->appendAnimation(*gravityAnimation);

				auto gemBottomGem = gameBoard.getGemFromCell(i, j + 1);
				if (gemBottomGem && !gemBottomGem->getAnimation()){
					auto bounceAnimation = new MoveGemAnimation();
					Point<float> bounceTop(destination.getX(), destination.getY() - BOUNCE_LENGTH);
					bounceAnimation->start(upperGem, destination, bounceTop, BOUNCE_STEPS, BOUNCE_PERIOD_SECONDS);
					composedAnimation->appendAnimation(*bounceAnimation);

					auto bounceReturnAnimation = new MoveGemAnimation();
					bounceReturnAnimation->start(upperGem, bounceTop, destination, BOUNCE_STEPS, BOUNCE_PERIOD_SECONDS);
					composedAnimation->appendAnimation(*bounceReturnAnimation);
				}
				upperGem->setAnimation(*composedAnimation);
			}
		}
	}
}
