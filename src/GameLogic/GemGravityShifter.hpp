#pragma once

#include <ctime>

namespace Board
{
	class Board;
}

namespace GameLogic {
	class GemGravityShifter
	{
	public:
		GemGravityShifter();

		void update(Board::Board& gameBoard);

	private:
		static const double SHIFT_PERIODE_SECS;

		std::clock_t lastUpdate;
	};
}
