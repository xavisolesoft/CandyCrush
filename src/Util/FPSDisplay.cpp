#include "FPSDisplay.hpp"

#include <sstream>
#include <string>

#include "../Render/GameRenderController.hpp"

#include "../Text/TextObject.hpp"
#include "../Text/TextRenderer.hpp"

#include "../Geometry/Point.hpp"

using namespace Util;
using namespace Geometry;
using namespace Text;

FPSDisplay::FPSDisplay() :
	nextTextGameObjectId(0)
{
}

void FPSDisplay::start()
{
	timeF = std::clock();
	fps = 0;
	fpsDisplayObject = &createTextGameObject(Point<float>(10, 0));
	fpsDisplayObject->setText("FPS: ");
}

void FPSDisplay::update()
{
	if ((std::clock() - timeF) >= CLOCKS_PER_SEC) {
		std::stringstream sstream;
		sstream << "FPS: " << fps;
		fpsDisplayObject->setText(std::move(sstream.str()));
		fps = 0;
		timeF = std::clock();
	}
	else {
		fps++;
	}
}

Text::TextObject& FPSDisplay::createTextGameObject(const Geometry::Point<float>& point)
{
	auto textObject = new TextObject(nextTextGameObjectId++);
	textObject->setWorldPos(point);

	auto textRenderer = new TextRenderer();
	Render::GameRenderController::getInstance().add(*textObject, *textRenderer);

	return *textObject;
}
