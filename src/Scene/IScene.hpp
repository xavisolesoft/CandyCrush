#pragma once

namespace Scene {
	class IScene
	{
	public:
		IScene();
		virtual ~IScene();
		
		virtual void init();
		virtual void start();
		virtual void update();
		virtual bool end();
	};
}
