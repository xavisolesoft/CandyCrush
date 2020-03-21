#pragma once

namespace Scene
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

		void generateStartConfiguration(Scene::Board& gameBoard, Gem::GemGenerator& gemGenerator);
	};
}
