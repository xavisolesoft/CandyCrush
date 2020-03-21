#pragma once

namespace Scene {
	class IScene
	{
	public:
		IScene();
		virtual ~IScene();
		
		virtual void init();
		virtual void update();
		virtual bool haveEnd();
	};
}
