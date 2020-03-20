#pragma once

#include <map>
#include <memory>

#include <king/Engine.h>

namespace Render
{
	class IRenderer;
}

namespace GameObject
{
	class IGameObject;
}

namespace Render {
	class RenderController
	{
	public:
		RenderController(King::Engine& engine);

		void update();

		void add(std::shared_ptr<const GameObject::IGameObject> gameObject, Render::IRenderer* renderer);
		void remove(std::shared_ptr<const GameObject::IGameObject> gameObject);


	private:
		std::map<std::shared_ptr<const GameObject::IGameObject>, Render::IRenderer*> renderers;

		King::Engine& engine;
	};
}
