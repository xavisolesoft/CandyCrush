#include "PlayerActions.hpp"

#include <vector>

#include "../Geometry/Point.hpp"

#include "../Scene/GameBoard.hpp"
#include "../Scene/Cell.hpp"
#include "../Scene/Gem.hpp"

#include "../GameLogic/LineMatcher.hpp"

#include "../Util/Debug.hpp"

using namespace GameLogic;
using namespace Geometry;
using namespace Scene;
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
	if (isDragStart(mouseButtonDown)) {
		dragAborted = false;
		updateDragStart(mouseX, mouseY);
	}
	if (!dragAborted) {
		if (isDragMove(mouseButtonDown)) {
			updateDragMove(mouseX, mouseY);
		}
		else if (isDragEnd(mouseButtonDown)) {
			updateDragEnd(mouseX, mouseY);
			dragAborted = false;
		}
	}

	prevMouseButtonDown = mouseButtonDown;
}

void PlayerActions::updateDragStart(float mouseX, float mouseY)
{
	dragStartCell = gameBoard.getCellFromWorldPos(mouseX, mouseY);
}

void PlayerActions::updateDragMove(float mouseX, float mouseY)
{
	const Scene::Cell* currentCell = gameBoard.getCellFromWorldPos(mouseX, mouseY);
	if (!dragStartCell) {
		dragStartCell = currentCell;
	}

	if (currentCell != dragStartCell && isAllowedMovement(dragStartCell, currentCell)) {
		auto currentGem = currentCell->getGem();

		auto dragStartGem = dragStartCell->getGem();
		gameBoard.swap(dragStartGem, currentGem);
		std::vector<std::vector<Point> > lines = lineMatcher.getBoardLines();
		if (lines.empty()) {
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

void PlayerActions::updateDragEnd(float mouseX, float mouseY)
{
	const Scene::Cell* currentCell = gameBoard.getCellFromWorldPos(mouseX, mouseY);
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

				gameBoard.swap(selectedCell->getGem(), currentGem);
				selectedCell = nullptr;
			}
		}
		else if (currentCell == dragStartCell) {
			selectedCell = currentCell;
			Util::Debug() << "SELECTED_CELL(" << selectedCell->getXCell() << ", " << selectedCell->getYCell() << ")"
				<< ", GEM(" << selectedCell->getGem()->getId() << ")";
		}
		else {

		}
	}
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
