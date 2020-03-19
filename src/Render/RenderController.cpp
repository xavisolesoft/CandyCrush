#include "RenderController.hpp"

#include "../GameObject/IGameObject.hpp"
#include "../Render/IRenderer.hpp"

using namespace GameObject;
using namespace Render;

RenderController::RenderController()
{
}

void RenderController::update()
{
	for (auto iter = renderers.begin(); iter != renderers.end(); ++iter) {
		IGameObject& gameOobject = *iter->first;
		IRenderer& renderer = *iter->second;
		renderer.update(gameOobject);
	}
}

void RenderController::add(GameObject::IGameObject* gameObject, Render::IRenderer* renderer)
{
	renderers[gameObject] = renderer;
}
