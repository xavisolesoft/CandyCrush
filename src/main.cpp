#define GLM_FORCE_RADIANS

#include <cstdlib>
#include <memory>
#include <string>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <king/Engine.h>
#include <king/Updater.h>

#include "Gem/GemGenerator.hpp"
#include "Scene/GameBoard.hpp"
#include "Scene/Cell.hpp"
#include "Gem/GemObject.hpp"

#include "Render/RenderController.hpp"

#include "GameLogic/PlayerActions.hpp"
#include "GameLogic/StarGameGemGenerator.hpp"
#include "GameLogic/LineRemover.hpp"
#include "GameLogic/SpawnGemGenerator.hpp"
#include "GameLogic/GemGravityShifter.hpp"
#include "GameLogic/GemAnimationUpdater.hpp"

#include "Animation/IAnimation.hpp"

//**********************************************************************

class ExampleGame : public King::Updater {
public:

	ExampleGame()
		: mEngine("./assets")
		, gemGenerator(Render::RenderController::getInstance())
		, playerActions(gameBoard)
	{
		Render::RenderController::getInstance().setEngine(&mEngine);
	}

	void Start()
	{
		gameBoard.setNumCells(8, 8);
		gameBoard.setCellHeight(45.0f);
		gameBoard.setCellWidth(45.0f);
		gameBoard.setTopLeft(Geometry::Point(320.0f, 100.0f));
		gameBoard.calculateBBoxes();

		gemGenerator.setSeed(60);
		GameLogic::StarGameGemGenerator startGameGenerator;
		startGameGenerator.generateStartConfiguration(gameBoard, gemGenerator);

		mEngine.Start(*this);
	}

	void Update()
	{
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);

		gemAnimationUpdater.update(gameBoard);

		Render::RenderController::getInstance().update();

		playerActions.update(mEngine.GetMouseButtonDown(), mEngine.GetMouseX(), mEngine.GetMouseY());

		if (!gameBoard.isAnyCellEmpty() && !gameBoard.isAnyGemAnimated()) {
			lineRemover.update(gameBoard);
		}

		gemGravityShifter.spawnGemsInFirstRowEmptyCells(gameBoard);

		spawnGemGenerator.spawnGemsInFirstRowEmptyCells(gameBoard, gemGenerator);
	}

private:
	King::Engine mEngine;
	Gem::GemGenerator gemGenerator;
	Scene::GameBoard gameBoard;
	GameLogic::PlayerActions playerActions;
	GameLogic::LineRemover lineRemover;
	GameLogic::SpawnGemGenerator spawnGemGenerator;
	GameLogic::GemGravityShifter gemGravityShifter;
	GameLogic::GemAnimationUpdater gemAnimationUpdater;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}


