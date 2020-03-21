#include "Cell.hpp"

#include "../Gem/GemObject.hpp"

using namespace GameBoard;
using namespace Gem;
using namespace Geometry;

Cell::Cell()
{
	
}

const BBox<float>& Cell::getBBox() const
{
	return bBox;
}

void Cell::setBBox(const BBox<float>& value)
{
	bBox = value;
}

std::shared_ptr<GemObject> Cell::getGem() const
{
	return gem;
}

void Cell::setGem(std::shared_ptr<GemObject> value)
{
	gem = std::move(value);
}

void Cell::setXCell(int value)
{
	xCell = value;
}

int Cell::getXCell() const
{
	return xCell;
}

void Cell::setYCell(int value)
{
	yCell = value;
}

int Cell::getYCell() const
{
	return yCell;
}

Point<int> Cell::getBoardPos() const
{
	return Point<int>(xCell, yCell);
}
