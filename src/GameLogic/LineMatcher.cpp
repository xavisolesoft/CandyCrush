#include "LineMatcher.hpp"


#include "../GameBoard/Board.hpp"

#include "../Geometry/Point.hpp"

#include "../Util/Debug.hpp"

using namespace GameLogic;
using namespace GameBoard;
using namespace Gem;
using namespace Geometry;

LineMatcher::LineMatcher(const Board& gameBoard) :
	gameBoard(gameBoard)
{
}

std::vector<std::vector<Point<int>> > LineMatcher::getBoardLines() const
{
	std::vector<std::vector<Point<int>> > machedLines;
	
	getVerticalBoardLines(machedLines);
	getHoritzontalBoardLines(machedLines);
	
	for (const std::vector<Point<int>>& line : machedLines) {
		Util::Debug debug;
		debug << "DETECTED_LINE ";
		for (const Point<int>& point : line) {
			debug << "(" << point.getX() << ", " << point.getY() << ")  ";
		}
	}

	return machedLines;
}

bool LineMatcher::containsCell(const std::vector<std::vector<Point<int>> >& lines, const Point<int>& point)
{
	for (const std::vector<Point<int> >& line : lines) {
		if (line.cend() != std::find(line.cbegin(), line.cend(), point)) {
			return true;
		}
	}
	return false;
}

void LineMatcher::getVerticalBoardLines(std::vector<std::vector<Point<int>> >& outLines) const
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
					std::vector<Point<int>> line;
					for (int k = numConsecutive - 1; k >= 0; --k) {
						line.push_back(Point<int>(i, j - k));
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

void LineMatcher::getHoritzontalBoardLines(std::vector<std::vector<Geometry::Point<int> > >& outLines) const
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
					std::vector<Point<int> > line;
					for (int k = numConsecutive; k > 0; --k) {
						line.push_back(Point<int>(i - k + 1, j));
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
