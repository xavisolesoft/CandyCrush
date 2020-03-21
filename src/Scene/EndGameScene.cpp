#include "EndGameScene.hpp"

#include <king/Engine.h>

#include "../GameLogic/StarGameGemGenerator.hpp"

#include "../GameBoard/Board.hpp"

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

}

void EndGameScene::update()
{
	Text::TextObject theEnd(0);
	theEnd.setWorldPos(Geometry::Point<float>(445, 260));
	theEnd.setText("The End");

	Text::TextRenderer textRenderer;
	textRenderer.setEngine(&engine);
	textRenderer.update(theEnd);
}

bool EndGameScene::end()
{
	return false;
}
