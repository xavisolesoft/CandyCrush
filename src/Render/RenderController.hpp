#pragma once

#include <map>

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
		RenderController();

		void update();

		void add(GameObject::IGameObject* gameObject, Render::IRenderer* renderer);

	private:
		std::map<GameObject::IGameObject*, Render::IRenderer*> renderers;
	};
}
