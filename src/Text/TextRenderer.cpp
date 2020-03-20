#include "../Text/TextRenderer.hpp"

#include <king/Engine.h>

#include "../Geometry/PointF.hpp"

#include "../Text/TextObject.hpp"

using namespace Text;
using namespace GameObject;

TextRenderer::TextRenderer()
{

}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::update(const IGameObject& gameObject)
{
	auto textObject = dynamic_cast<const TextObject&>(gameObject);
	engine->Write(textObject.getText().c_str(), textObject.getWorldPos().getX(), textObject.getWorldPos().getY());
}
