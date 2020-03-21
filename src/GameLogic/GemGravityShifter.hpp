#pragma once

#include <ctime>

namespace GameBoard
{
	class Board;
}

namespace GameLogic {
	class GemGravityShifter
	{
	public:
		GemGravityShifter();

		void update(GameBoard::Board& gameBoard);

	private:
		static const double SHIFT_PERIODE_SECS;

		std::clock_t lastUpdate;
	};
}
