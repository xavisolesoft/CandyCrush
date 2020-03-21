#pragma once

namespace GameBoard
{
	class Board;
}

namespace GameLogic {
	class GemAnimationUpdater
	{
	public:
		GemAnimationUpdater();

		void update(GameBoard::Board& gameBoard);
	};
}
