#pragma once

#include <king/Engine.h>

namespace GameObject
{
	class IGameObject;
}

namespace Render {
	class IRenderer
	{
	public:
		IRenderer();
		virtual ~IRenderer();

		void setEngine(King::Engine* value);

		virtual void update(const GameObject::IGameObject& gameObject) = 0;

	protected:
		King::Engine* engine;
	};
}
