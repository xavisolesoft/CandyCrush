#pragma once

#include <ctime>

namespace Scene
{
	class GameBoard;
}

namespace Gem {
	class GemGenerator;
}

namespace GameLogic {
	class SpawnGemGenerator
	{
	public:
		SpawnGemGenerator();

		void spawnGemsInFirstRowEmptyCells(Scene::GameBoard& gameBoard, Gem::GemGenerator& gemGenerator);

	private:
		static const double SPAWN_PERIODE_SECS;

		std::clock_t lastUpdate;
	};
}
