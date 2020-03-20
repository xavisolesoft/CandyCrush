#pragma once

#include <king/Engine.h>

#include "../Render/IRenderer.hpp"

namespace GameObject
{
	class IGameObject;
}

namespace Text {
	class TextRenderer :
		public Render::IRenderer
	{
	public:
		TextRenderer();
		~TextRenderer();

		virtual void update(const GameObject::IGameObject& gameObject) override;
	};
}
