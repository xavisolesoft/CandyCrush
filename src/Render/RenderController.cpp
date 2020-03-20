#include "RenderController.hpp"

#include "../GameObject/IGameObject.hpp"
#include "../Gem/GemRenderer.hpp"
#include "../Render/IRenderer.hpp"

using namespace GameObject;
using namespace Render;

RenderController::RenderController(King::Engine& engine) :
	engine(engine)
{
}

void RenderController::update()
{
	for (auto iter = renderers.begin(); iter != renderers.end(); ++iter) {
		const IGameObject& gameObject = *iter->first;
		IRenderer& renderer = *iter->second;
		renderer.update(gameObject);
	}
}

void RenderController::add(const GameObject::IGameObject& gameObject, Render::IRenderer& renderer)
{
	renderer.setEngine(&engine);
	renderers[&gameObject] = &renderer;
}

void RenderController::remove(const IGameObject& gameObject)
{
	renderers.erase(&gameObject);
}
