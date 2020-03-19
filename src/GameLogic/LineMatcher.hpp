#pragma once

#include "../Scene/Gem.hpp"

#include <vector>

namespace Geometry
{
	class Point;
}

namespace Scene
{
	class GameBoard;
	class Cell;
}

namespace GameLogic {
	class LineMatcher
	{
	public:
		LineMatcher(const Scene::GameBoard& gameBoard);
		
		std::vector<std::vector<Geometry::Point> > getBoardLines() const;

		static bool containsCell(const std::vector<std::vector<Geometry::Point> >& lines, const Geometry::Point& point);
		
	private:
		void getVerticalBoardLines(std::vector<std::vector<Geometry::Point> >& outLines) const;
		void getHoritzontalBoardLines(std::vector<std::vector<Geometry::Point> >& outLines) const;

		const Scene::GameBoard& gameBoard;
	};
}
