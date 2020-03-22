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
	
	private:
		static const float BOUNCE_LENGTH;
		static const float BOUNCE_SPEED;

		static const float GRAVITY_SPEED;
		static const int GRAVITY_STEP_FOR_CELL_CHANGE;
	};
}
