#pragma once

#include <vector>

#include "../GameLogic/LineMatcher.hpp"

namespace Board
{
	class Board;
}

namespace Geometry
{
	template<class T>
	class Point;
}

namespace GameLogic {
	class LineRemover
	{
	public:
		LineRemover();

		void update(Board::Board& gameBoard);
	};
}
