#pragma once

namespace Scene
{
	class GameBoard;
}

namespace Gem {
	class GemGenerator;
}

namespace GameLogic {
	class StarGameGemGenerator
	{
	public:
		StarGameGemGenerator();

		void generateStartConfiguration(Scene::GameBoard& gameBoard, Gem::GemGenerator& gemGenerator);
	};
}
