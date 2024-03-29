#include "LineRemover.hpp"

#include "GameBoard/Board.hpp"
#include "Geometry/Point.hpp"

#include "Gem/DestroyGemAnimation.hpp"

#include "Util/Debug.hpp"

using namespace GameLogic;
using namespace GameBoard;
using namespace Geometry;

LineRemover::LineRemover()
{
}

void LineRemover::update(Board& gameBoard)
{
	GameLogic::LineMatcher lineMatcher(gameBoard);
	std::vector<std::vector<Geometry::Point<int>>> lines = lineMatcher.getBoardLines();
	for (const std::vector<Geometry::Point<int>> line : lines) {
		for (const Geometry::Point<int>& point : line) {
			auto gem = gameBoard.getGemFromCell((int)point.getX(), (int)point.getY());
			long gemId = -1;
			if (gem && gem->isUserInteractionEnabled()) {
				gemId = gem->getId();
				auto destroyGemAnimation = new Gem::DestroyGemAnimation();
				destroyGemAnimation->setGem(gem,
					[&gameBoard, point]() {
						gameBoard.setGemToCell((int)point.getX(), (int)point.getY(), nullptr);
					});
				gem->setAnimation(*destroyGemAnimation);
			}
			Util::Debug() << "REOVED_CELL(" << (int)point.getX() << ", " << (int)point.getY() << "), GEM(" << gemId << ")";
		}
	}
}
