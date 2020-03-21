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
	class GamePlayScene
	{
	public:
		GamePlayScene(King::Engine& engine,
					GameBoard::Board& gameBoard,
					Gem::GemGenerator& gemGenerator);
		~GamePlayScene();
		
		void start();
		void update();
		bool end();

	private:
		King::Engine& engine;
		GameBoard::Board& gameBoard;
		Gem::GemGenerator& gemGenerator;
		GameLogic::LineRemover lineRemover;
		GameLogic::PlayerActions playerActions;
		GameLogic::GameTimeController gameTimeController;
		GameLogic::GemAnimationUpdater gemAnimationUpdater;
		GameLogic::SpawnGemGenerator spawnGemGenerator;
		GameLogic::GemGravityShifter gemGravityShifter;
	};
}
