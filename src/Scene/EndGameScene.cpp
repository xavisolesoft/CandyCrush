#include "EndGameScene.hpp"

#include "../Render/GUIRenderController.hpp"

#include "../Text/TextObject.hpp"
#include "../Text/TextRenderer.hpp"

using namespace Scene;

EndGameScene::EndGameScene() :
	isFirstUpdate(true)
{
}

EndGameScene::~EndGameScene()
{
	
}

void EndGameScene::start()
{
	createTheEndTextObject();
}

void EndGameScene::update()
{
	if (isFirstUpdate) {
		start();
		isFirstUpdate = false;
	}
}

bool EndGameScene::haveEnd()
{
	return false;
}

void EndGameScene::createTheEndTextObject() const
{
	auto theEndTextObject = new Text::TextObject(0);
	theEndTextObject->setWorldPos(Geometry::Point<float>(445, 48));
	theEndTextObject->setText("The End");

	auto textRenderer = new Text::TextRenderer();
	Render::GUIRenderController::getInstance().add(*theEndTextObject, *textRenderer);
}
