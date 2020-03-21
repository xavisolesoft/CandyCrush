#include "GamePlayScene.hpp"

#include <king/Engine.h>

#include "../Render/GUIRenderController.hpp"

#include "../GameLogic/StarGameGemGenerator.hpp"

#include "../GameBoard/Board.hpp"

using namespace Scene;

const int GamePlayScene::GAME_DURATION_SECS = 60;

GamePlayScene::GamePlayScene(King::Engine& engine,
							GameBoard::Board& gameBoard,
							Gem::GemGenerator& gemGenerator) :
	engine(engine),
	gameBoard(gameBoard),
	gemGenerator(gemGenerator),
	playerActions(gameBoard),
	isFirstUpdate(isFirstUpdate),
	scoreCounter(gemGenerator)
{
}

GamePlayScene::~GamePlayScene()
{
	
}

void GamePlayScene::init()
{
	GameLogic::StarGameGemGenerator startGameGenerator;
	startGameGenerator.generateStartConfiguration(gameBoard, gemGenerator);
}

void GamePlayScene::start()
{
	gameTimeController.start(GAME_DURATION_SECS);
	scoreCounter.start();
}

void GamePlayScene::update()
{
	if (isFirstUpdate) {
		start();
		isFirstUpdate = false;
	}

	gameTimeController.update();
	scoreCounter.update();

	gemAnimationUpdater.update(gameBoard);

	if (!gameTimeController.isTheEnd()) {
		playerActions.update(engine.GetMouseButtonDown(), engine.GetMouseX(), engine.GetMouseY());
	}

	if (!gameBoard.isAnyCellEmpty() && !gameBoard.isAnyGemAnimated()) {
		lineRemover.update(gameBoard);
	}

	gemGravityShifter.update(gameBoard);

	spawnGemGenerator.update(gameBoard, gemGenerator);

	if (haveEnd()) {
		Render::GUIRenderController::getInstance().removeAll();
	}
}

bool GamePlayScene::haveEnd()
{
	return gameTimeController.isTheEnd() && !gameBoard.isAnyGemAnimated();
}
