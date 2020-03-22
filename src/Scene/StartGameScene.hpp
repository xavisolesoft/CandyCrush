#pragma once

#include <string>

#include "Scene/IScene.hpp"

namespace King
{
	class Engine;
}

namespace Geometry
{
	template<class T>
	class Point;
}

namespace Scene {
	class StartGameScene :
		public IScene
	{
	public:
		StartGameScene(King::Engine& engine);
		~StartGameScene();
		
		void start();
		void update() override;
		bool haveEnd() override;

	private:
		void createTextGameObject(std::string text, const Geometry::Point<float>& point);

		King::Engine& engine;
		bool isFirstUpdate;
		bool sceneEnd;
		bool prevButtonDown;
		int nextTextGameObjectId;
	};
}
