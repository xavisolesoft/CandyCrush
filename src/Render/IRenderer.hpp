#pragma once

namespace GameObject
{
	class IGameObject;
}

namespace Render {
	class IRenderer
	{
	public:
		virtual ~IRenderer() {};
		virtual bool update(const GameObject::IGameObject& gameObject) = 0;
	};
}
