#include "StartGameScene.hpp"

#include "../Render/GUIRenderController.hpp"

#include "../Text/TextObject.hpp"
#include "../Text/TextRenderer.hpp"

#include "../Geometry/Point.hpp"

using namespace Scene;

StartGameScene::StartGameScene(King::Engine& engine) :
	engine(engine),
	isFirstUpdate(true),
	sceneEnd(false),
	prevButtonDown(false),
	nextTextGameObjectId(0)
{
}

StartGameScene::~StartGameScene()
{
	
}

void StartGameScene::start()
{
	createTextGameObject("Click to Start", Geometry::Point<float>(405, 48));
}

void StartGameScene::update()
{
	if (isFirstUpdate) {
		start();
		isFirstUpdate = false;
	}

	if (!engine.GetMouseButtonDown() && prevButtonDown){
		sceneEnd = true;
	}

	if (haveEnd()) {
		Render::GUIRenderController::getInstance().removeAll();
	}

	prevButtonDown = engine.GetMouseButtonDown();
}

bool StartGameScene::haveEnd()
{
	return sceneEnd;
}

void StartGameScene::createTextGameObject(std::string text, const Geometry::Point<float>& point)
{
	auto theEndTextObject = new Text::TextObject(nextTextGameObjectId++);
	theEndTextObject->setWorldPos(point);
	theEndTextObject->setText(std::move(text));

	auto textRenderer = new Text::TextRenderer();
	Render::GUIRenderController::getInstance().add(*theEndTextObject, *textRenderer);
}
