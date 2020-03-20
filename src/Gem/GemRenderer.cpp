#include "../Gem/GemRenderer.hpp"

#include <king/Engine.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Geometry/Point.hpp"

#include "../Gem/GemObject.hpp"

#include "../Util/EngineDebug.hpp"

using namespace Gem;
using namespace GameObject;

GemRenderer::GemRenderer()
{

}

GemRenderer::~GemRenderer()
{
}

void GemRenderer::update(const IGameObject& gameObject)
{
	auto gem = dynamic_cast<const GemObject&>(gameObject);
	Geometry::Point pos = gem.getWorldPos();
	King::Engine::Texture texture = getGemTexture(gem.getGemType());
	glm::mat4 transformation;

	transformation = glm::translate(transformation, glm::vec3(pos.getX(), pos.getY(), 0.0f));

	float rotation = gem.getRotation();
	if (rotation) {
		transformation = glm::rotate(transformation, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	}


	float scale = gem.getScale();
	if (scale != 1.0f) {
		float transToOriginX = engine->GetTextureWidth(texture) / 2.0f;
		float transToOriginY = engine->GetTextureHeight(texture) / 2.0f;
		transformation = glm::translate(transformation, glm::vec3(transToOriginX, transToOriginY, 0.0f));
		transformation = glm::scale(transformation, glm::vec3(scale));
		transformation = glm::translate(transformation, glm::vec3(-transToOriginX, -transToOriginY, 0.0f));
	}

	engine->Render(texture, transformation);

	Util::EngineDebug(*engine).Write(std::to_string(gem.getId()).c_str(),
		pos.getX(),
		pos.getY());
}

King::Engine::Texture GemRenderer::getGemTexture(Gem::GemType gemType)
{
	switch (gemType)
	{
	case Gem::GemType::BLUE:
		return King::Engine::TEXTURE_BLUE;
	case Gem::GemType::GREEN:
		return King::Engine::TEXTURE_GREEN;
	case Gem::GemType::PURPLE:
		return King::Engine::TEXTURE_PURPLE;
	case Gem::GemType::RED:
		return King::Engine::TEXTURE_RED;
	default:
		return King::Engine::TEXTURE_YELLOW;
	}
}
