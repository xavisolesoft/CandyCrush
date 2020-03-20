#pragma once

#include <map>
#include <memory>

#include <king/Engine.h>

#include "../Util/Singleton.hpp"

namespace Render
{
	class IRenderer;
}

namespace GameObject
{
	class IGameObject;
}

namespace Render {
	class RenderController :
		public Util::ISingleton<RenderController>
	{
	public:
		RenderController();
		~RenderController();

		void setEngine(King::Engine* engine);

		void update();

		void add(const GameObject::IGameObject& gameObject, Render::IRenderer& renderer);
		void remove(const GameObject::IGameObject& gameObject);

		void removeAll();

	private:
		std::map<const GameObject::IGameObject*, Render::IRenderer*> renderers;

		King::Engine* engine;
	};
}
