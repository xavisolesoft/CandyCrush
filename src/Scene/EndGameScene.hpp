#pragma once

#include "../GameLogic/LineRemover.hpp"
#include "../GameLogic/PlayerActions.hpp"
#include "../GameLogic/GameTimeController.hpp"
#include "../GameLogic/GemAnimationUpdater.hpp"
#include "../GameLogic/SpawnGemGenerator.hpp"
#include "../GameLogic/GemGravityShifter.hpp"

namespace GameBoard
{
	class Board;
}

namespace Gem
{
	class GemGenerator;
}

namespace King
{
	class Engine;
}

namespace Scene {
	class EndGameScene
	{
	public:
		EndGameScene(King::Engine& engine);
		~EndGameScene();
		
		void start();
		void update();
		bool end();

	private:
		King::Engine& engine;
	};
}
