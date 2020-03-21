#pragma once

namespace GameBoard
{
	class Board;
}

namespace Gem {
	class GemGenerator;
}

namespace King
{
	class Engine;
}

namespace GameLogic {
	class StarGameGemGenerator
	{
	public:
		StarGameGemGenerator();

		void generateStartConfiguration(GameBoard::Board& gameBoard, Gem::GemGenerator& gemGenerator);
	};
}
