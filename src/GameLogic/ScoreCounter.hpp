#pragma once

namespace Geometry
{
	template<class T>
	class Point;
}

namespace Text
{
	class TextObject;
}

namespace Gem
{
	class GemGenerator;
}

namespace GameLogic {
	class ScoreCounter
	{
	public:
		ScoreCounter(Gem::GemGenerator& gemGenerator);

		void start();
		void update();

	private:
		Text::TextObject& createTextGameObject(const Geometry::Point<float>& point);

		Text::TextObject* scoreObject;
		Gem::GemGenerator& gemGenerator;
	};
}
