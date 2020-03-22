#include "ScoreCounter.hpp"

#include <string>
#include <sstream>

#include "Gem/GemGenerator.hpp"

#include "Render/GameRenderController.hpp"

#include "Text/TextObject.hpp"
#include "Text/TextRenderer.hpp"

#include "Geometry/Point.hpp"

using namespace GameLogic;
using namespace Gem;
using namespace Text;
using namespace Render;
using namespace Geometry;

ScoreCounter::ScoreCounter(GemGenerator& gemGenerator) :
	gemGenerator(gemGenerator)
{
}

void ScoreCounter::start()
{
	scoreObject = &createTextGameObject(Point<float>(300, 45));
	scoreObject->setText("Score: ");
	gemGenerator.resetNumDestroyedGems();
}

void ScoreCounter::update()
{
	std::stringstream sstream;
	sstream << "Score: " << gemGenerator.getNumDestroyedGems();
	scoreObject->setText(std::move(sstream.str()));
}

Text::TextObject& GameLogic::ScoreCounter::createTextGameObject(const Geometry::Point<float>& point)
{
	auto textObject = new TextObject(0);
	textObject->setWorldPos(point);

	auto textRenderer = new TextRenderer();
	GameRenderController::getInstance().add(*textObject, *textRenderer);

	return *textObject;
}
