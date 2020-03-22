#pragma once

#include <map>
#include <memory>

#include "RenderController.hpp"

#include "Util/Singleton.hpp"

namespace Render
{
	class IRenderer;
}

namespace GameObject
{
	class IGameObject;
}

namespace Render {
	class GameRenderController :
		public Util::ISingleton<GameRenderController>,
		public RenderController
	{
		friend class Util::ISingleton<GameRenderController>;

	private:
		GameRenderController();
	};
}
