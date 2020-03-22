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
	class GUIRenderController :
		public Util::ISingleton<GUIRenderController>,
		public RenderController
	{
		friend class Util::ISingleton<GUIRenderController>;

	private:
		GUIRenderController();
	};
}
