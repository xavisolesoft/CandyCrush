#pragma once

#include "../Gem/GemObject.hpp"

#include <vector>

namespace Geometry
{
	class PointF;
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
		
		std::vector<std::vector<Geometry::PointF> > getBoardLines() const;

		static bool containsCell(const std::vector<std::vector<Geometry::PointF> >& lines, const Geometry::PointF& point);
		
	private:
		void getVerticalBoardLines(std::vector<std::vector<Geometry::PointF> >& outLines) const;
		void getHoritzontalBoardLines(std::vector<std::vector<Geometry::PointF> >& outLines) const;

		const Scene::GameBoard& gameBoard;
	};
}
