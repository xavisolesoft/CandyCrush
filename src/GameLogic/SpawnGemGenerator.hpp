#pragma once

#include <ctime>

namespace Scene
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

		void update(Scene::Board& gameBoard, Gem::GemGenerator& gemGenerator);

	private:
		static const double SPAWN_PERIODE_SECS;

		std::clock_t lastUpdate;
	};
}
