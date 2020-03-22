#pragma once

#include <memory>

#include <ctime>
#include <string>

#include "Text/TextObject.hpp"


namespace GameLogic {
	class GameTimeController
	{
	public:
		GameTimeController();

		void start(std::clock_t gameDurationSecs);
		void update();

		std::clock_t getGameRemaningTimeSecs() const;
		std::string getGameRemaningTimeStr() const;

		bool isTheEnd() const;

	private:
		std::clock_t gameStartTimeSecs;
		std::clock_t gameEndTimeSecs;

		std::unique_ptr<Text::TextObject> timerTittle;
		std::unique_ptr<Text::TextObject> timerObject;

		bool started;
	};
}
