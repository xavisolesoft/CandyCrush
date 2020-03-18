#pragma once

#include <string>
#include <sstream>

#include <king/Engine.h>

namespace Util {
	class EngineDebug
	{
	public:
		EngineDebug(King::Engine& mEngine);
		~EngineDebug();

		void Write(const char* text, float x, float y, float rotation = 0.0f);
		
	private:
		King::Engine& engine;
	};
}
