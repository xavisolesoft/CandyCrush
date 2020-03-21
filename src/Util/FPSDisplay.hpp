#pragma once

#include <ctime>
#include <string>

namespace Geometry
{
	template<class T>
	class Point;
}

namespace Text
{
	class TextObject;
}

namespace Util {
	class FPSDisplay
	{
	public:
		FPSDisplay();

		void start();
		void update();

	private:
		Text::TextObject& createTextGameObject(const Geometry::Point<float>& point);

		std::clock_t timeF;
		int fps;
		int nextTextGameObjectId;
		Text::TextObject* fpsDisplayObject;
	};
}
