#include "PlayerActions.hpp"

#include <vector>

#include "../Geometry/Point.hpp"

#include "../GameBoard/Board.hpp"
#include "../GameBoard/Cell.hpp"
#include "../Gem/GemObject.hpp"

#include "../Gem/MoveGemAnimation.hpp"
#include "../Animation/ComposedSequentialAnimation.hpp"

#include "../Util/Debug.hpp"

using namespace GameLogic;
using namespace Geometry;
using namespace Gem;
using namespace Scene;
using namespace Animation;
using namespace Util;

PlayerActions::PlayerActions(Board& gameBoard) :
	gameBoard(gameBoard),
	lineMatcher(gameBoard),
	selectedCell(nullptr),
	prevMouseButtonDown(false),
	dragStartCell(nullptr),
	dragAborted(false)
{
}

void PlayerActions::update(bool mouseButtonDown, float mouseX, float mouseY)
{
	std::shared_ptr<GemObject> prevSelectedGem = nullptr;
	if (selectedCell) {
		prevSelectedGem = selectedCell->getGem();
	}

	const Scene::Cell* currentCell = gameBoard.getCellFromWorldPos(mouseX, mouseY);
	if(currentCell && currentCell->getGem() && currentCell->getGem()->isUserInteractionEnabled())
	if (isDragStart(mouseButtonDown)) {
		dragAborted = false;
		updateDragStart(currentCell);
	}
	if (!dragAborted) {
		if (isDragMove(mouseButtonDown)) {
			updateDragMove(currentCell);
		}
		else if (isDragEnd(mouseButtonDown)) {
			updateDragEnd(currentCell);
			dragAborted = false;
		}
	}

	if (prevSelectedGem) {
		prevSelectedGem->setScale(1.0f);
	}

	if (selectedCell && selectedCell->getGem()) {
		selectedCell->getGem()->setScale(1.3f);
	}

	prevMouseButtonDown = mouseButtonDown;
}

void PlayerActions::updateDragStart(const Scene::Cell* currentCell)
{
	dragStartCell = currentCell;
}

void PlayerActions::updateDragMove(const Scene::Cell* currentCell)
{
	if (!dragStartCell) {
		dragStartCell = currentCell;
	}

	if (currentCell != dragStartCell && isAllowedMovement(dragStartCell, currentCell)) {
		trySwapGems(*dragStartCell, *currentCell);
		selectedCell = nullptr;
		dragAborted = true;
	}
}

void PlayerActions::updateDragEnd(const Scene::Cell* currentCell)
{
	if (currentCell) {
		Util::Debug() << "CLICKED_CELL(" << currentCell->getXCell() << ", " << currentCell->getYCell() << ")"
			<< ", GEM(" << currentCell->getGem()->getId() << ")";

		if (selectedCell) {
			if (currentCell != selectedCell && isAllowedMovement(selectedCell, currentCell)) {
				trySwapGems(*selectedCell, *currentCell);
				selectedCell = nullptr;
			}
			else {
				selectedCell = dragStartCell;
			}
		}
		else if (currentCell == dragStartCell) {
			selectedCell = currentCell;
			Util::Debug() << "SELECTED_CELL(" << selectedCell->getXCell() << ", " << selectedCell->getYCell() << ")"
				<< ", GEM(" << selectedCell->getGem()->getId() << ")";
		}
	}
}

void PlayerActions::trySwapGems(const Cell& cell1, const Cell& cell2)
{
	auto gem1 = cell1.getGem();
	auto gem2 = cell2.getGem();

	setSwapAnimations(gem1, gem2);
	gameBoard.swap(gem2, gem1);
	std::vector<std::vector<Point<int>> > lines = lineMatcher.getBoardLines();
	if (!LineMatcher::containsCell(lines, Point<int>(cell1.getBoardPos())) &&
		!LineMatcher::containsCell(lines, Point<int>(cell2.getBoardPos()))) {
		appendSwapReturnAnimations(gem2, gem1);
		gameBoard.swap(gem2, gem1);
	}
	else {
		Util::Debug() << "SWAP_CELL(" << cell1.getXCell() << ", " << cell1.getYCell() << ")"
			<< ", GEM(" << gem1->getId() << ")"
			<< "  ->  "
			<< "SWAP_CELL(" << cell2.getXCell() << ", " << cell2.getYCell() << ")"
			<< ", GEM(" << gem2->getId() << ")";
	}
}

void PlayerActions::setSwapAnimations(std::shared_ptr<GemObject> gem1, std::shared_ptr<GemObject> gem2)
{
	auto animation1 = new MoveGemAnimation();
	animation1->start(gem1, gem1->getWorldPos(), gem2->getWorldPos(), 10, 0.01f);
	gem1->setAnimation(*animation1);

	auto animation2 = new MoveGemAnimation();
	animation2->start(gem2, gem2->getWorldPos(), gem1->getWorldPos(), 10, 0.01f);
	gem2->setAnimation(*animation2);
}

void PlayerActions::appendSwapReturnAnimations(std::shared_ptr<GemObject> gem1, std::shared_ptr<GemObject> gem2)
{
	auto swapReturnAnimtion1 = new MoveGemAnimation();
	swapReturnAnimtion1->start(gem1, gem1->getWorldPos(), gem2->getWorldPos(), 10, 0.01f);
	auto composedAnimation1 = new ComposedSequentialAnimation();
	composedAnimation1->appendAnimation(*gem1->getAnimation());
	composedAnimation1->appendAnimation(*swapReturnAnimtion1);
	gem1->setAnimation(*composedAnimation1);

	auto swapReturnAnimtion2 = new MoveGemAnimation();
	swapReturnAnimtion2->start(gem2, gem2->getWorldPos(), gem1->getWorldPos(), 10, 0.01f);
	auto composedAnimation2 = new ComposedSequentialAnimation();
	composedAnimation2->appendAnimation(*gem2->getAnimation());
	composedAnimation2->appendAnimation(*swapReturnAnimtion2);
	gem2->setAnimation(*composedAnimation2);
}

bool PlayerActions::isAllowedMovement(const Cell* originCell, const Cell* destinationCell)
{
	if (!originCell || !destinationCell ||
		!originCell->getGem() || !destinationCell->getGem() ||
		!originCell->getGem()->isUserInteractionEnabled() || !destinationCell->getGem()->isUserInteractionEnabled()) {
		return false;
	}

	Geometry::Vector<int> move = destinationCell->getBoardPos() - originCell->getBoardPos();
	return move == Geometry::Vector<int>(0, 1) ||
		move == Geometry::Vector<int>(0, -1) ||
		move == Geometry::Vector<int>(1, 0) ||
		move == Geometry::Vector<int>(-1, 0);
}

bool PlayerActions::isDragStart(bool mouseButtonDown) const
{
	return !prevMouseButtonDown && mouseButtonDown;
}

bool PlayerActions::isDragMove(bool mouseButtonDown) const
{
	return prevMouseButtonDown && mouseButtonDown;
}

bool PlayerActions::isDragEnd(bool mouseButtonDown) const
{
	return prevMouseButtonDown && !mouseButtonDown;
}
