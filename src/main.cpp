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
#include "GameBoard/Board.hpp"
#include "GameBoard/Cell.hpp"
#include "Gem/GemObject.hpp"

#include "Render/RenderController.hpp"

#include "Text/TextObject.hpp"
#include "Text/TextRenderer.hpp"

#include "GameLogic/PlayerActions.hpp"
#include "GameLogic/StarGameGemGenerator.hpp"
#include "GameLogic/LineRemover.hpp"
#include "GameLogic/SpawnGemGenerator.hpp"
#include "GameLogic/GemGravityShifter.hpp"
#include "GameLogic/GemAnimationUpdater.hpp"
#include "GameLogic/GameTimeController.hpp"

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
		gameBoard.setTopLeft(Geometry::Point<float>(320.0f, 100.0f));
		gameBoard.calculateBBoxes();

		gemGenerator.setSeed(60);
		GameLogic::StarGameGemGenerator startGameGenerator;
		startGameGenerator.generateStartConfiguration(gameBoard, gemGenerator);

		gameTimeController.start(60);

		mEngine.Start(*this);
	}

	void Update()
	{
		if (!gameTimeController.isTheEnd()) {
			mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);

			gameTimeController.update();

			gemAnimationUpdater.update(gameBoard);

			Render::RenderController::getInstance().update();

			playerActions.update(mEngine.GetMouseButtonDown(), mEngine.GetMouseX(), mEngine.GetMouseY());

			if (!gameBoard.isAnyCellEmpty() && !gameBoard.isAnyGemAnimated()) {
				lineRemover.update(gameBoard);
			}

			gemGravityShifter.update(gameBoard);

			spawnGemGenerator.update(gameBoard, gemGenerator);
		}
		else {
			mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);

			Text::TextObject theEnd(0);
			theEnd.setWorldPos(Geometry::Point<float>(445, 260));
			theEnd.setText("The End");
			Text::TextRenderer textRenderer;
			textRenderer.setEngine(&mEngine);
			textRenderer.update(theEnd);
		}


		/*
		if (mEngine.GetMouseButtonDown()) {
			std::cout << "CLICK---->  " << mEngine.GetMouseX() << ", " << mEngine.GetMouseY() << std::endl;
		}
		*/
	}

private:
	King::Engine mEngine;
	Gem::GemGenerator gemGenerator;
	Scene::Board gameBoard;
	GameLogic::PlayerActions playerActions;
	GameLogic::LineRemover lineRemover;
	GameLogic::SpawnGemGenerator spawnGemGenerator;
	GameLogic::GemGravityShifter gemGravityShifter;
	GameLogic::GemAnimationUpdater gemAnimationUpdater;
	GameLogic::GameTimeController gameTimeController;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}
