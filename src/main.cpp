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

#include "Scene/GamePlayScene.hpp"

#include "Render/RenderController.hpp"

#include "Text/TextObject.hpp"
#include "Text/TextRenderer.hpp"

#include "Animation/IAnimation.hpp"

//**********************************************************************

class ExampleGame : public King::Updater {
public:

	ExampleGame()
		: mEngine("./assets")
		, gemGenerator(Render::RenderController::getInstance())
		, gamePlayScene(mEngine, gameBoard, gemGenerator)
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

		gamePlayScene.start();

		mEngine.Start(*this);
	}

	void Update()
	{
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);

		if (!gamePlayScene.end()) {
			gamePlayScene.update();

			Render::RenderController::getInstance().update();
		}
		else {
			mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);

			Render::RenderController::getInstance().update();

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
	GameBoard::Board gameBoard;
	Scene::GamePlayScene gamePlayScene;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}
