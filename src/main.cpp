#define GLM_FORCE_RADIANS

#include <king/Engine.h>
#include <king/Updater.h>

#include "Gem/GemGenerator.hpp"

#include "GameBoard/Board.hpp"

#include "Scene/StartGameScene.hpp"
#include "Scene/GamePlayScene.hpp"
#include "Scene/EndGameScene.hpp"

#include "Render/GameRenderController.hpp"
#include "Render/GUIRenderController.hpp"

#include "Util/FPSDisplay.hpp"

//**********************************************************************

class ExampleGame : public King::Updater {
public:

	ExampleGame()
		: mEngine("./assets")
		, gemGenerator(Render::GameRenderController::getInstance())
		, startGameScene(mEngine)
		, gamePlayScene(mEngine, gameBoard, gemGenerator)
	{
		Render::GameRenderController::getInstance().setEngine(&mEngine);
		Render::GUIRenderController::getInstance().setEngine(&mEngine);
	}

	void Start()
	{
		gameBoard.setNumCells(8, 8);
		gameBoard.setCellHeight(45.0f);
		gameBoard.setCellWidth(45.0f);
		gameBoard.setTopLeft(Geometry::Point<float>(320.0f, 100.0f));
		gameBoard.calculateBBoxes();

		gemGenerator.setSeed(60);

		gamePlayScene.init();

		fpsDisplay.start();

		mEngine.Start(*this);
	}

	void Update()
	{
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);

		if (!startGameScene.haveEnd()){
			startGameScene.update();
		}
		else if (!gamePlayScene.haveEnd()) {
			gamePlayScene.update();
		}
		else {
			endGameScene.update();
		}

		fpsDisplay.update();

		Render::GameRenderController::getInstance().update();
		Render::GUIRenderController::getInstance().update();
	}

private:
	King::Engine mEngine;
	Gem::GemGenerator gemGenerator;
	GameBoard::Board gameBoard;
	Scene::StartGameScene startGameScene;
	Scene::GamePlayScene gamePlayScene;
	Scene::EndGameScene endGameScene;
	Util::FPSDisplay fpsDisplay;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}
