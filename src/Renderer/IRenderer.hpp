#pragma once

namespace Render {
	class IRenderer
	{
	public:
		virtual ~IRenderer() {};
		virtual bool update() = 0;
	};
}
