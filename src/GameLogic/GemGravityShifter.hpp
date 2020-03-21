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
		static const int BOUNCE_STEPS;
		static const float BOUNCE_PERIOD_SECONDS;

		static const int GRAVITY_STEPS;
		static const float GRAVITY_PERIOD_SECONDS;
		static const int GRAVITY_STEP_FOR_CELL_CHANGE;
	};
}
