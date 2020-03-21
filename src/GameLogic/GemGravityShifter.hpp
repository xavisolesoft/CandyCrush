#pragma once

#include <ctime>

namespace Scene
{
	class Board;
}

namespace GameLogic {
	class GemGravityShifter
	{
	public:
		GemGravityShifter();

		void update(Scene::Board& gameBoard);

	private:
		static const double SHIFT_PERIODE_SECS;

		std::clock_t lastUpdate;
	};
}
