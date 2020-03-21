#include "EndGameScene.hpp"

#include <king/Engine.h>

#include "../GameLogic/StarGameGemGenerator.hpp"

#include "../GameBoard/Board.hpp"

#include "../Render/GUIRenderController.hpp"

#include "../Text/TextObject.hpp"
#include "../Text/TextRenderer.hpp"

using namespace Scene;

EndGameScene::EndGameScene(King::Engine& engine) :
	engine(engine)
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
	
}

bool EndGameScene::end()
{
	return false;
}

void EndGameScene::createTheEndTextObject() const
{
	auto theEndTextObject = new Text::TextObject(0);
	theEndTextObject->setWorldPos(Geometry::Point<float>(445, 260));
	theEndTextObject->setText("The End");

	auto textRenderer = new Text::TextRenderer();
	Render::GUIRenderController::getInstance().add(*theEndTextObject, *textRenderer);
}
