#include "PlayerActions.hpp"

#include <vector>

#include "../Geometry/Point.hpp"

#include "../Scene/GameBoard.hpp"
#include "../Scene/Cell.hpp"
#include "../Scene/Gem.hpp"

#include "../GameLogic/LineMatcher.hpp"

#include "../Animation/MoveGemAnimation.hpp"
#include "../Animation/ComposedSequentialAnimation.hpp"

#include "../Util/Debug.hpp"

using namespace GameLogic;
using namespace Geometry;
using namespace Scene;
using namespace Animation;
using namespace Util;

PlayerActions::PlayerActions(GameBoard& gameBoard, const LineMatcher& lineMatcher) :
	gameBoard(gameBoard),
	lineMatcher(lineMatcher),
	selectedCell(nullptr),
	prevMouseButtonDown(false),
	dragStartCell(nullptr),
	dragAborted(false)
{
}

void PlayerActions::update(bool mouseButtonDown, float mouseX, float mouseY)
{
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
		auto currentGem = currentCell->getGem();

		auto dragStartGem = dragStartCell->getGem();
		setSwapAnimations(currentGem, dragStartGem);
		gameBoard.swap(dragStartGem, currentGem);
		std::vector<std::vector<Point> > lines = lineMatcher.getBoardLines();
		if (lines.empty()) {
			appendSwapReturnAnimations(dragStartGem, currentGem);
			gameBoard.swap(dragStartGem, currentGem);

		}
		else {
			Util::Debug() << "SWAP_CELL(" << dragStartCell->getXCell() << ", " << dragStartCell->getYCell() << ")"
				<< ", GEM(" << dragStartCell->getGem()->getId() << ")"
				<< "  ->  "
				<< "SWAP_CELL(" << currentCell->getXCell() << ", " << currentCell->getYCell() << ")"
				<< ", GEM(" << currentGem->getId() << ")";
		}
		selectedCell = nullptr;
		dragAborted = true;
	}
}

void PlayerActions::updateDragEnd(const Scene::Cell* currentCell)
{
	if (currentCell) {
		auto currentGem = currentCell->getGem();
		Util::Debug() << "CLICKED_CELL(" << currentCell->getXCell() << ", " << currentCell->getYCell() << ")"
			<< ", GEM(" << currentGem->getId() << ")";

		if (selectedCell) {
			if (currentCell != selectedCell && isAllowedMovement(selectedCell, currentCell)) {
				Util::Debug() << "SWAP_CELL(" << selectedCell->getXCell() << ", " << selectedCell->getYCell() << ")"
					<< ", GEM(" << selectedCell->getGem()->getId() << ")"
					<< "  ->  "
					<< "SWAP_CELL(" << currentCell->getXCell() << ", " << currentCell->getYCell() << ")"
					<< ", GEM(" << currentGem->getId() << ")";

				setSwapAnimations(currentGem, selectedCell->getGem());
				gameBoard.swap(selectedCell->getGem(), currentGem);
				selectedCell = nullptr;
			}
		}
		else if (currentCell == dragStartCell) {
			selectedCell = currentCell;
			Util::Debug() << "SELECTED_CELL(" << selectedCell->getXCell() << ", " << selectedCell->getYCell() << ")"
				<< ", GEM(" << selectedCell->getGem()->getId() << ")";
		}
	}
}

void PlayerActions::setSwapAnimations(std::shared_ptr<Gem> gem1, std::shared_ptr<Gem> gem2)
{
	auto animation1 = new MoveGemAnimation();
	animation1->start(gem1, gem1->getWorldPos(), gem2->getWorldPos(), 30, 0.01f);
	gem1->setAnimation(*animation1);

	auto animation2 = new MoveGemAnimation();
	animation2->start(gem2, gem2->getWorldPos(), gem1->getWorldPos(), 30, 0.01f);
	gem2->setAnimation(*animation2);
}

void PlayerActions::appendSwapReturnAnimations(std::shared_ptr<Gem> gem1, std::shared_ptr<Gem> gem2)
{
	auto swapReturnAnimtion1 = new MoveGemAnimation();
	swapReturnAnimtion1->start(gem1, gem1->getWorldPos(), gem2->getWorldPos(), 30, 0.01f);
	auto composedAnimation1 = new ComposedSequentialAnimation();
	composedAnimation1->appendAnimation(*gem1->getAnimation());
	composedAnimation1->appendAnimation(*swapReturnAnimtion1);
	gem1->setAnimation(*composedAnimation1);

	auto swapReturnAnimtion2 = new MoveGemAnimation();
	swapReturnAnimtion2->start(gem2, gem2->getWorldPos(), gem1->getWorldPos(), 30, 0.01f);
	auto composedAnimation2 = new ComposedSequentialAnimation();
	composedAnimation2->appendAnimation(*gem2->getAnimation());
	composedAnimation2->appendAnimation(*swapReturnAnimtion2);
	gem2->setAnimation(*composedAnimation2);
}

bool PlayerActions::isAllowedMovement(const Cell* originCell, const Cell* destinationCell)
{
	if (!originCell || !destinationCell) {
		return false;
	}

	Geometry::Vector move = destinationCell->getBoardPos() - originCell->getBoardPos();
	return move == Geometry::Vector(0, 1) ||
		move == Geometry::Vector(0, -1) ||
		move == Geometry::Vector(1, 0) ||
		move == Geometry::Vector(-1, 0);
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
