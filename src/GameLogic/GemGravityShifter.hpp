#pragma once

#include <ctime>

namespace Scene
{
	class GameBoard;
}

namespace GameLogic {
	class GemGravityShifter
	{
	public:
		GemGravityShifter();

		void spawnGemsInFirstRowEmptyCells(Scene::GameBoard& gameBoard);

	private:
		static const double SHIFT_PERIODE_SECS;

		std::clock_t lastUpdate;
	};
}
