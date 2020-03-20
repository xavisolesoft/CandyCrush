#pragma once

#include <vector>

#include "../GameLogic/LineMatcher.hpp"

namespace Scene
{
	class GameBoard;
}

namespace Geometry
{
	class Point;
}

namespace GameLogic {
	class LineRemover
	{
	public:
		LineRemover();

		void update(Scene::GameBoard& gameBoard);
	};
}
