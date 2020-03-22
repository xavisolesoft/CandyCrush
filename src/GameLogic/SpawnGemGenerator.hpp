#pragma once

#include <ctime>

namespace GameBoard
{
	class Board;
}

namespace Gem {
	class GemGenerator;
}

namespace GameLogic {
	class SpawnGemGenerator
	{
	public:
		SpawnGemGenerator();

		void update(GameBoard::Board& gameBoard, Gem::GemGenerator& gemGenerator);
	};
}
