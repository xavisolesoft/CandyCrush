#include "Board.hpp"

#include "../Geometry/Point.hpp"
#include "../Gem/GemObject.hpp"

using namespace GameBoard;
using namespace Gem;
using namespace Geometry;

Board::Board()
{

}

BBox<float> Board::getBBox() const
{
	return bBox;
}

BBox<float> Board::getCellBBox(int x, int y) const
{
	if (isValidCell(x, y)) {
		return cells[x][y].getBBox();
	}

	return BBox<float>();
}

int Board::getNumXCells() const
{
	return cells.size();
}

int Board::getNumYCells() const
{
	if (cells.empty()) {
		return 0;
	}

	return cells.front().size();
}

void Board::setNumCells(int numXCells, int numYCells)
{
	cells.resize(numXCells, std::vector<Cell>(numYCells));

	for (int i = 0; i < numXCells; ++i) {
		for(int j = 0; j < numYCells; ++j) {
			cells[i][j].setXCell(i);
			cells[i][j].setYCell(j);
		}
	}
}

void Board::setCellWidth(float value)
{
	cellWidth = value;
}

float Board::getCellWidth() const
{
	return cellWidth;
}

void Board::setCellHeight(float value)
{
	cellHeight = value;
}

float Board::getCellHeight() const
{
	return cellHeight;
}

void Board::setTopLeft(const Point<float>& point)
{
	topLeft = point;
}

void Board::setGemToCell(int x, int y, std::shared_ptr<GemObject> gem)
{
	if (isValidCell(x, y)) {
		cells[x][y].setGem(gem);
		if (gem && gem->isUserInteractionEnabled()) {
			gem->setWorldPos(cells[x][y].getBBox().getTopLeft());
		}
	}
}

std::shared_ptr<GemObject> Board::getGemFromCell(int x, int y) const
{
	if (isValidCell(x, y)) {
		return cells[x][y].getGem();
	}

	return nullptr;
}

void Board::swap(std::shared_ptr<GemObject> gem1, std::shared_ptr<GemObject> gem2)
{
	const Point<float>& worldPos1 = gem1->getWorldPos();
	const Point<float>& worldPos2 = gem2->getWorldPos();
	const Cell* cell1 = getCellFromWorldPos(worldPos1.getX(), worldPos1.getY());
	const Cell* cell2 = getCellFromWorldPos(worldPos2.getX(), worldPos2.getY());
	setGemToCell(cell1->getXCell(), cell1->getYCell(), gem2);
	setGemToCell(cell2->getXCell(), cell2->getYCell(), gem1);
}

void Board::swap(int xCell1, int yCell1, int xCell2, int yCell2)
{
	auto gem1 = getGemFromCell(xCell1, yCell1);
	auto gem2 = getGemFromCell(xCell2, yCell2);
	setGemToCell(xCell1, yCell1, gem2);
	setGemToCell(xCell2, yCell2, gem1);
}

void Board::calculateBBoxes()
{
	calculateSceneBBox();
}

const Cell* Board::getCellFromWorldPos(float xWorld, float yWorld) const
{
	Point<float> point(xWorld, yWorld);
	if (!bBox.contains(point)) {
		return nullptr;
	}

	int xCell = static_cast<int>((xWorld - topLeft.getX()) / cellWidth);
	int yCell = static_cast<int>((yWorld - topLeft.getY()) / cellHeight);
	
	if (isValidCell(xCell, yCell)) {
		return &cells[xCell][yCell];
	}
	
	return nullptr;
}

Point<float> Board::getWorldPosFromCell(int xCell, int yCell) const
{
	if (!isValidCell(xCell, yCell)) {
		return topLeft;
	}

	return topLeft + Point<float>(cellWidth*xCell, cellHeight*yCell);

	return Point<float>();
}

bool Board::isValidCell(int i, int j) const
{
	return i >= 0 &&
		j >= 0 &&
		i < getNumXCells() &&
		j < getNumYCells();
}

bool Board::isAnyCellEmpty() const
{
	for (size_t i = 0; i < cells.size(); ++i) {
		for (size_t j = 0; j < cells[i].size(); ++j) {
			if (!cells[i][j].getGem()) {
				return true;
			}
		}
	}

	return false;
}

bool Board::isAnyGemAnimated() const
{
	for (size_t i = 0; i < cells.size(); ++i) {
		for (size_t j = 0; j < cells[i].size(); ++j) {
			if (cells[i][j].getGem() && cells[i][j].getGem()->getAnimation()) {
				return true;
			}
		}
	}

	return false;
}

void Board::calculateSceneBBox()
{
	bBox.setStartPoint(topLeft);
	bBox.expand(Point<float>(topLeft.getX() + getNumXCells()*cellWidth,
							topLeft.getY() + getNumYCells()*cellHeight));

	for (size_t i = 0; i < cells.size(); ++i) {
		for (size_t j = 0; j < cells[i].size(); ++j) {
			calculateCellBox(i, j);
		}
	}
}

void Board::calculateCellBox(int i, int j)
{
	if (isValidCell(i, j)) {
		BBox<float> bBox;
		Point<float> cellTopLeft(topLeft.getX() + i * cellWidth,
								topLeft.getY() + j * cellHeight);

		bBox.setStartPoint(cellTopLeft);
		bBox.expand(Point<float>(cellTopLeft.getX() + cellWidth,
								cellTopLeft.getY() + cellHeight));

		cells[i][j].setBBox(bBox);
	}
}
