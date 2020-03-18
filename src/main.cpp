#define GLM_FORCE_RADIANS

#include <cstdlib>
#include <memory>
#include <string>
#include <iostream>
#include <ctime>

#include <king/Engine.h>
#include <king/Updater.h>

#include "Scene/GemGenerator.hpp"
#include "Scene/GameBoard.hpp"
#include "Scene/Cell.hpp"
#include "Scene/Gem.hpp"

#include "GameLogic/PlayerActions.hpp"
#include "GameLogic/LineMatcher.hpp"

#include "Util/EngineDebug.hpp"

//**********************************************************************

class ExampleGame : public King::Updater {
public:

	ExampleGame()
		: mEngine("./assets")
		, mRotation(0.0f)
		, mYellowDiamondX(100.0f)
		, mYellowDiamondY(100.0f)
		, lineMatcher(gameBoard)
		, playerActions(gameBoard, lineMatcher)
	{
		
	}

	void Start() {
		gameBoard.setNumCells(8, 8);
		gameBoard.setCellHeight(45.0f);
		gameBoard.setCellWidth(45.0f);
		gameBoard.setTopLeft(Geometry::Point(320.0f, 100.0f));
		gameBoard.calculateBBoxes();

		for (int j = 0; j < gameBoard.getNumYCells(); ++j) {
			for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
				gameBoard.setGemToCell(i, j, gemGenerator.createNextGem());
			}
		}

		mEngine.Start(*this);
	}
#include <iostream>
	void Update() {
		static std::clock_t lastUpdate = std::clock();
		
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);

		for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
			for (int j = 0; j < gameBoard.getNumYCells(); ++j) {
				Geometry::BBox bBox = gameBoard.getCellBBox(i, j);
				Geometry::Point topLeft = bBox.getTopLeft();
				std::shared_ptr<Scene::Gem> gem = gameBoard.getGemFromCell(i, j);
				if (gem) {
					mEngine.Render(getGemTexture(gem->getGemType()),
									topLeft.getX(),
									topLeft.getY());
					Util::EngineDebug(mEngine).Write(std::to_string(gem->getId()).c_str(),
													topLeft.getX(),
													topLeft.getY());
				}
			}
		}

		playerActions.update(mEngine.GetMouseButtonDown(), mEngine.GetMouseX(), mEngine.GetMouseY());

		if (mEngine.GetMouseButtonDown()) {
			std::vector<std::vector<Geometry::Point> > lines = lineMatcher.getBoardLines();
			for (const std::vector<Geometry::Point> line : lines) {
				for (const Geometry::Point& point : line) {
					gameBoard.setGemToCell((int)point.getX(), (int)point.getY(), nullptr);
				}
			}
		}

		if ((std::clock() - lastUpdate) / (double)CLOCKS_PER_SEC >= 1.0){
			for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
				for (int j = gameBoard.getNumYCells() - 1; j > 0; --j) {
					auto gem = gameBoard.getGemFromCell(i, j);
					if (!gem) {
						gameBoard.swap(i, j, i, j - 1);
					}
				}
			}

			for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
				auto gem = gameBoard.getGemFromCell(i, 0);
				if (!gem) {
					gemGenerator.createNextGem();
					gameBoard.setGemToCell(i, 0, gemGenerator.createNextGem());
				}
			}

			lastUpdate = std::clock();
		}
		

/*
		mEngine.Render(King::Engine::TEXTURE_GREEN, 650.0f, 100.0f);
		mEngine.Render(King::Engine::TEXTURE_RED, 100.0f, 450.0f);
		mEngine.Render(King::Engine::TEXTURE_BLUE, 650.0f, 450.0f);

		

		mEngine.Write("Green", 650.0f, 140.0f);
		mEngine.Write("Red", 100.0f, 490.0f);
		mEngine.Write("Blue", 650.0f, 490.0f);

		const char text[] = "This rotates at 5/PI Hz";
		mRotation += mEngine.GetLastFrameSeconds();
		mEngine.Write(text, mEngine.GetWidth() / 2.0f, mEngine.GetHeight() / 2.0f, mRotation * 2.5f);

		if (mEngine.GetMouseButtonDown()) {
			mYellowDiamondX = mEngine.GetMouseX();
			mYellowDiamondY = mEngine.GetMouseY();
		}
		mEngine.Render(King::Engine::TEXTURE_YELLOW, mYellowDiamondX, mYellowDiamondY);
		mEngine.Write("Click to", mYellowDiamondX, mYellowDiamondY + 40.0f);
		mEngine.Write("move me!", mYellowDiamondX, mYellowDiamondY + 70.0f);

		*/
	}

	static King::Engine::Texture getGemTexture(Scene::GemType gemType)
	{
		switch (gemType)
		{
		case Scene::GemType::BLUE:
			return King::Engine::TEXTURE_BLUE;
		case Scene::GemType::GREEN:
			return King::Engine::TEXTURE_GREEN;
		case Scene::GemType::PURPLE:
			return King::Engine::TEXTURE_PURPLE;
		case Scene::GemType::RED:
			return King::Engine::TEXTURE_RED;
		default:
			return King::Engine::TEXTURE_YELLOW;
		}
	}

private:
	King::Engine mEngine;
	float mRotation;
	float mYellowDiamondX;
	float mYellowDiamondY;
	Scene::GameBoard gameBoard;
	GameLogic::LineMatcher lineMatcher;
	GameLogic::PlayerActions playerActions;
	Scene::GemGenerator gemGenerator;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}


