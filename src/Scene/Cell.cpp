#include "Cell.hpp"

#include "Gem.hpp"

using namespace Scene;
using namespace Geometry;

Cell::Cell()
{
	
}

const BBox& Cell::getBBox() const
{
	return bBox;
}

void Cell::setBBox(const BBox& value)
{
	bBox = value;
}

std::shared_ptr<Gem> Cell::getGem() const
{
	return gem;
}

void Cell::setGem(std::shared_ptr<Gem> value)
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

Point Cell::getBoardPos() const
{
	return Point(xCell, yCell);
}
