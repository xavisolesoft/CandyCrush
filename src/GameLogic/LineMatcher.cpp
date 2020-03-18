#include "LineMatcher.hpp"

#include "../Scene/GameBoard.hpp"

#include "../Geometry/Point.hpp"

using namespace GameLogic;
using namespace Scene;
using namespace Geometry;

LineMatcher::LineMatcher(const GameBoard& gameBoard) :
	gameBoard(gameBoard)
{
}

std::vector<std::vector<Point> > LineMatcher::getBoardLines() const
{
	std::vector<std::vector<Point> > machedLines;
	
	getVerticalBoardLines(machedLines);
	getHoritzontalBoardLines(machedLines);
	
	return machedLines;
}

void LineMatcher::getVerticalBoardLines(std::vector<std::vector<Geometry::Point>>& outLines) const
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
			}
			else {
				if (numConsecutive >= 3) {
					std::vector<Point> line;
					for (int k = numConsecutive - 1; k >= 0; --k) {
						line.push_back(Point((float)i, (float)j - k));
					}
					outLines.push_back(line);
				}
				if (gem) {
					gemType = gem->getGemType();
					numConsecutive = 1;
				}
			}
		}
	}
}

void LineMatcher::getHoritzontalBoardLines(std::vector<std::vector<Geometry::Point>>& outLines) const
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
			}
			else {
				if (numConsecutive >= 3) {
					std::vector<Point> line;
					for (int k = numConsecutive; k > 0; --k) {
						line.push_back(Point((float)i - k, (float)j));
					}
					outLines.push_back(line);
				}
				if (gem) {
					gemType = gem->getGemType();
					numConsecutive = 1;
				}
			}
		}
	}
}
