#pragma once

namespace Animation {
	class IAnimation
	{
	public:
		virtual ~IAnimation() {};
		virtual bool update() = 0;
	};
}
