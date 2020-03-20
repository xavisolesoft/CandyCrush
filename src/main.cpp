#define GLM_FORCE_RADIANS

#include <cstdlib>
#include <memory>
#include <string>
#include <iostream>
#include <ctime>

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
#include "GameLogic/LineMatcher.hpp"

#include "Animation/IAnimation.hpp"
#include "Gem/DestroyGemAnimation.hpp"

#include "Util/Debug.hpp"
#include "Util/EngineDebug.hpp"

//**********************************************************************

class ExampleGame : public King::Updater {
public:

	ExampleGame()
		: mEngine("./assets")
		, lineMatcher(gameBoard)
		, playerActions(gameBoard, lineMatcher)
		, renderController(mEngine)
		, gemGenerator(renderController)
	{
		
	}

	void Start()
	{
		gameBoard.setNumCells(8, 8);
		gameBoard.setCellHeight(45.0f);
		gameBoard.setCellWidth(45.0f);
		gameBoard.setTopLeft(Geometry::Point(320.0f, 100.0f));
		gameBoard.calculateBBoxes();

		for (int j = 0; j < gameBoard.getNumYCells(); ++j) {
			for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
				auto gem = gemGenerator.createNextGem();
				gameBoard.setGemToCell(i, j, gem);
			}
		}

		std::vector<std::vector<Geometry::Point> > lines;
		do {
			lines = lineMatcher.getBoardLines();

			for (const std::vector<Geometry::Point> line : lines) {
				for (const Geometry::Point& point : line) {
					auto gem = gemGenerator.createNextGem();
					gameBoard.setGemToCell((int)point.getX(), (int)point.getY(), gem);
				}
			}
		} while (!lines.empty());

		mEngine.Start(*this);
	}

	void Update()
	{
		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);

		for (int i = 0; i < gameBoard.getNumXCells(); ++i) {
			for (int j = 0; j < gameBoard.getNumYCells(); ++j) {
				std::shared_ptr<Gem::GemObject> gem = gameBoard.getGemFromCell(i, j);
				if (gem) {
					gem->animationUpdate();
				}
			}
		}

		renderController.update();

		Geometry::Point boardCenter = gameBoard.getBBox().getCenter();
		mEngine.Write("1111111", boardCenter.getX(), boardCenter.getY());

		playerActions.update(mEngine.GetMouseButtonDown(), mEngine.GetMouseX(), mEngine.GetMouseY());

		if (!gameBoard.isAnyCellEmpty() && !gameBoard.isAnyGemAnimated()) {
			std::vector<std::vector<Geometry::Point> > lines = lineMatcher.getBoardLines();
			for (const std::vector<Geometry::Point> line : lines) {
				for (const Geometry::Point& point : line) {
					auto gem = gameBoard.getGemFromCell((int)point.getX(), (int)point.getY());
					long gemId = -1;
					if (gem) {
						gemId = gem->getId();
						auto destroyGemAnimation = new Animation::DestroyGemAnimation();
						destroyGemAnimation->setGem(gem,
													[this, gem, point](){
														gameBoard.setGemToCell((int)point.getX(), (int)point.getY(), nullptr);
													});
						gem->setAnimation(*destroyGemAnimation);
					}
					Util::Debug() << "REOVED_CELL(" << (int)point.getX() << ", " << (int)point.getY() << "), GEM(" << gemId << ")";
				}
			}
		}

		static std::clock_t lastUpdate = std::clock();
		if ((std::clock() - lastUpdate) / (double)CLOCKS_PER_SEC >= 0.1){
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
					gameBoard.setGemToCell(i, 0, gemGenerator.createNextGem());
				}
			}

			lastUpdate = std::clock();
		}
	}

private:
	King::Engine mEngine;
	Scene::GameBoard gameBoard;
	GameLogic::LineMatcher lineMatcher;
	GameLogic::PlayerActions playerActions;
	Render::RenderController renderController;
	Gem::GemGenerator gemGenerator;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}


