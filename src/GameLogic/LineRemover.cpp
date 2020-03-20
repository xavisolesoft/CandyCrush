#include "LineRemover.hpp"

#include "../Scene/GameBoard.hpp"
#include "../Geometry/PointF.hpp"

#include "../Gem/DestroyGemAnimation.hpp"

#include "../Util/Debug.hpp"

using namespace GameLogic;
using namespace Scene;
using namespace Geometry;

LineRemover::LineRemover()
{
}

void LineRemover::update(GameBoard& gameBoard)
{
	GameLogic::LineMatcher lineMatcher(gameBoard);
	std::vector<std::vector<Geometry::PointF> > lines = lineMatcher.getBoardLines();
	for (const std::vector<Geometry::PointF> line : lines) {
		for (const Geometry::PointF& point : line) {
			auto gem = gameBoard.getGemFromCell((int)point.getX(), (int)point.getY());
			long gemId = -1;
			if (gem) {
				gemId = gem->getId();
				auto destroyGemAnimation = new Animation::DestroyGemAnimation();
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
