#pragma once

namespace Board
{
	class Board;
}

namespace Gem {
	class GemGenerator;
}

namespace GameLogic {
	class StarGameGemGenerator
	{
	public:
		StarGameGemGenerator();

		void generateStartConfiguration(Board::Board& gameBoard, Gem::GemGenerator& gemGenerator);
	};
}
