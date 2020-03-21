#pragma once

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
	};
}
