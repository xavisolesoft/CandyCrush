#pragma once

#include "../Gem/GemObject.hpp"

#include <vector>

namespace Geometry
{
	template<class T>
	class Point;
}

namespace Scene
{
	class Board;
	class Cell;
}

namespace GameLogic {
	class LineMatcher
	{
	public:
		LineMatcher(const Scene::Board& gameBoard);
		
		std::vector<std::vector<Geometry::Point<int>> > getBoardLines() const;

		static bool containsCell(const std::vector<std::vector<Geometry::Point<int>> >& lines, const Geometry::Point<int>& point);
		
	private:
		void getVerticalBoardLines(std::vector<std::vector<Geometry::Point<int>> >& outLines) const;
		void getHoritzontalBoardLines(std::vector<std::vector<Geometry::Point<int>> >& outLines) const;

		const Scene::Board& gameBoard;
	};
}
