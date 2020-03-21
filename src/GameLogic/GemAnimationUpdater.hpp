#pragma once

namespace Board
{
	class Board;
}

namespace GameLogic {
	class GemAnimationUpdater
	{
	public:
		GemAnimationUpdater();

		void update(Board::Board& gameBoard);
	};
}
