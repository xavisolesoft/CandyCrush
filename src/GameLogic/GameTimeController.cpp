#include "GameTimeController.hpp"

#include <sstream>

#include "../Text/TextRenderer.hpp"
#include "../Text/TextObject.hpp"

#include "../Render/RenderController.hpp"

using namespace GameLogic;
using namespace Text;
using namespace Render;

GameTimeController::GameTimeController()
{
}

void GameTimeController::start(std::clock_t gameDurationSecs)
{
	timerTittle.reset(new TextObject(0));
	timerTittle->setWorldPos(Geometry::Point(44.0f, 386.0f));
	timerTittle->setText("Time:");
	RenderController::getInstance().add(*timerTittle, *(new TextRenderer()));

	timerObject.reset(new TextObject(1));
	timerObject->setWorldPos(Geometry::Point(76.0f, 445.0f));
	RenderController::getInstance().add(*timerObject, *(new TextRenderer()));

	gameStartTimeSecs = std::clock();
	gameEndTimeSecs = gameStartTimeSecs + gameDurationSecs*CLOCKS_PER_SEC;
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

bool GameTimeController::haveGameEnded() const
{
	return gameEndTimeSecs <= std::clock();
}
