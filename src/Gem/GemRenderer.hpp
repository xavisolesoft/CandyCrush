#pragma once

#include <king/Engine.h>

#include "../Gem/GemObject.hpp"
#include "../Render/IRenderer.hpp"

namespace GameObject
{
	class IGameObject;
}

namespace Gem {
	class GemRenderer :
		public Render::IRenderer
	{
	public:
		GemRenderer();
		~GemRenderer();

		virtual void update(const GameObject::IGameObject& gameObject) override;

	private:
		static King::Engine::Texture getGemTexture(Gem::GemType gemType);
	};
}
