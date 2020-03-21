#include "GameTimeController.hpp"

#include <sstream>

#include "../Text/TextRenderer.hpp"
#include "../Text/TextObject.hpp"

#include "../Render/GUIRenderController.hpp"

using namespace GameLogic;
using namespace Text;
using namespace Render;

GameTimeController::GameTimeController() :
	started(false)
{
}

void GameTimeController::start(std::clock_t gameDurationSecs)
{
	timerTittle.reset(new TextObject(0));
	timerTittle->setWorldPos(Geometry::Point<float>(44.0f, 386.0f));
	timerTittle->setText("Time:");
	GUIRenderController::getInstance().add(*timerTittle, *(new TextRenderer()));

	timerObject.reset(new TextObject(1));
	timerObject->setWorldPos(Geometry::Point<float>(70.0f, 445.0f));
	GUIRenderController::getInstance().add(*timerObject, *(new TextRenderer()));

	gameStartTimeSecs = std::clock();
	gameEndTimeSecs = gameStartTimeSecs + gameDurationSecs*CLOCKS_PER_SEC;

	started = true;
}

void GameTimeController::update()
{
	timerObject->setText(getGameRemaningTimeStr());
}

std::clock_t GameTimeController::getGameRemaningTimeSecs() const
{
	return (gameEndTimeSecs - std::clock())/CLOCKS_PER_SEC;
}

std::string GameTimeController::getGameRemaningTimeStr() const
{
	std::stringstream stringStream;
	std::clock_t gameElapsedTime = getGameRemaningTimeSecs();
	stringStream.fill('0');
	stringStream.width(2);
	stringStream << gameElapsedTime / 60 << ":";
	stringStream.width(2);
	stringStream << gameElapsedTime%60;
	return stringStream.str();
}

bool GameTimeController::isTheEnd() const
{
	return started && gameEndTimeSecs <= std::clock();
}
