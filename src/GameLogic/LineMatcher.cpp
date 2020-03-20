#include "LineMatcher.hpp"


#include "../Scene/GameBoard.hpp"

#include "../Geometry/PointF.hpp"

#include "../Util/Debug.hpp"

using namespace GameLogic;
using namespace Scene;
using namespace Gem;
using namespace Geometry;

LineMatcher::LineMatcher(const GameBoard& gameBoard) :
	gameBoard(gameBoard)
{
}

std::vector<std::vector<PointF> > LineMatcher::getBoardLines() const
{
	std::vector<std::vector<PointF> > machedLines;
	
	getVerticalBoardLines(machedLines);
	getHoritzontalBoardLines(machedLines);
	
	for (const std::vector<PointF>& line : machedLines) {
		Util::Debug debug;
		debug << "DETECTED_LINE ";
		for (const PointF& point : line) {
			debug << "(" << point.getX() << ", " << point.getY() << ")  ";
		}
	}

	return machedLines;
}

bool LineMatcher::containsCell(const std::vector<std::vector<PointF> >& lines, const PointF& point)
{
	for (const std::vector<PointF>& line : lines) {
		if (line.cend() != std::find(line.cbegin(), line.cend(), point)) {
			return true;
		}
	}
	return false;
}

void LineMatcher::getVerticalBoardLines(std::vector<std::vector<PointF>>& outLines) const
{
	for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
		int numConsecutive = 0;
		GemType gemType = GemType::UNDEFINED;
		if (gameBoard.getNumYCells() > 0) {
			auto gem = gameBoard.getGemFromCell(i, 0);
			if (gem) {
				gemType = gem->getGemType();
				numConsecutive = 1;
			}
		}

		for (int j = 1; j < gameBoard.getNumYCells(); ++j) {
			auto gem = gameBoard.getGemFromCell(i, j);
			if (gem && gem->getGemType() == gemType) {
				numConsecutive++;
				if (numConsecutive >= 3) {
					std::vector<PointF> line;
					for (int k = numConsecutive - 1; k >= 0; --k) {
						line.push_back(PointF((float)i, (float)j - k));
					}
					outLines.push_back(line);
				}
			}
			else {
				if (gem) {
					gemType = gem->getGemType();
				}
				else {
					gemType = GemType::UNDEFINED;
				}
				numConsecutive = 1;
			}
		}
	}
}

void LineMatcher::getHoritzontalBoardLines(std::vector<std::vector<Geometry::PointF>>& outLines) const
{
	for (int j = 0; j < gameBoard.getNumYCells(); ++j) {
		int numConsecutive = 0;
		GemType gemType = GemType::UNDEFINED;
		if (gameBoard.getNumXCells() > 0) {
			auto gem = gameBoard.getGemFromCell(0, j);
			if (gem) {
				gemType = gem->getGemType();
				numConsecutive = 1;
			}
		}

		for (int i = 1; i < gameBoard.getNumXCells(); ++i) {
			auto gem = gameBoard.getGemFromCell(i, j);
			if (gem && gem->getGemType() == gemType) {
				numConsecutive++;
				if (numConsecutive >= 3) {
					std::vector<PointF> line;
					for (int k = numConsecutive; k > 0; --k) {
						line.push_back(PointF((float)i - k + 1, (float)j));
					}
					outLines.push_back(line);
				}
			}
			else{
				if (gem) {
					gemType = gem->getGemType();
				}
				else {
					gemType = GemType::UNDEFINED;
				}
				numConsecutive = 1;
			}
		}
	}
}
