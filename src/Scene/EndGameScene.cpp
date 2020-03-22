#include "EndGameScene.hpp"

#include "../Render/GUIRenderController.hpp"

#include "../Text/TextObject.hpp"
#include "../Text/TextRenderer.hpp"

using namespace Scene;
using namespace Geometry;

EndGameScene::EndGameScene() :
	isFirstUpdate(true)
{
}

EndGameScene::~EndGameScene()
{
	
}

void EndGameScene::start()
{
	createTheEndTextObject(Point<float>(450, 50));
	createTheEndTextObject(Point<float>(450, 458));
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

void EndGameScene::createTheEndTextObject(const Point<float>& pos) const
{
	auto theEndTextObject = new Text::TextObject(0);
	theEndTextObject->setWorldPos(pos);
	theEndTextObject->setText("The End");

	auto textRenderer = new Text::TextRenderer();
	Render::GUIRenderController::getInstance().add(*theEndTextObject, *textRenderer);
}
