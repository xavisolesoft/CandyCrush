#pragma once

#include "Scene/IScene.hpp"
#include "GameLogic/LineRemover.hpp"
#include "GameLogic/PlayerActions.hpp"
#include "GameLogic/GameTimeController.hpp"
#include "GameLogic/GemAnimationUpdater.hpp"
#include "GameLogic/SpawnGemGenerator.hpp"
#include "GameLogic/GemGravityShifter.hpp"
#include "GameLogic/ScoreCounter.hpp"

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
	class GamePlayScene :
		public IScene
	{
	public:
		GamePlayScene(King::Engine& engine,
					GameBoard::Board& gameBoard,
					Gem::GemGenerator& gemGenerator);
		~GamePlayScene();
		
		void init() override;
		void start();
		void update() override;
		bool haveEnd() override;

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
		GameLogic::ScoreCounter scoreCounter;
		
		bool isFirstUpdate;

		static const int GAME_DURATION_SECS;
	};
}
