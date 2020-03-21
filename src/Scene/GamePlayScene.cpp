#include "GamePlayScene.hpp"

#include <king/Engine.h>

#include "../GameLogic/StarGameGemGenerator.hpp"

#include "../GameBoard/Board.hpp"

using namespace Scene;

GamePlayScene::GamePlayScene(King::Engine& engine,
							GameBoard::Board& gameBoard,
							Gem::GemGenerator& gemGenerator) :
	engine(engine),
	gameBoard(gameBoard),
	gemGenerator(gemGenerator),
	playerActions(gameBoard)
{
}

GamePlayScene::~GamePlayScene()
{
	
}

void GamePlayScene::start()
{
	GameLogic::StarGameGemGenerator startGameGenerator;
	startGameGenerator.generateStartConfiguration(gameBoard, gemGenerator);

	gameTimeController.start(8);
}

void GamePlayScene::update()
{
	gameTimeController.update();

	gemAnimationUpdater.update(gameBoard);

	playerActions.update(engine.GetMouseButtonDown(), engine.GetMouseX(), engine.GetMouseY());

	if (!gameBoard.isAnyCellEmpty() && !gameBoard.isAnyGemAnimated()) {
		lineRemover.update(gameBoard);
	}

	gemGravityShifter.update(gameBoard);

	spawnGemGenerator.update(gameBoard, gemGenerator);
}

bool GamePlayScene::end()
{
	return gameTimeController.isTheEnd();
}
