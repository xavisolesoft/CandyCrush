#pragma once

#include "../Scene/IScene.hpp"

#include "../Geometry/Point.hpp"

namespace Scene {
	class EndGameScene :
		public IScene
	{
	public:
		EndGameScene();
		~EndGameScene();
		
		void start();
		void update() override;
		bool haveEnd() override;

	private:
		void createTheEndTextObject(const Geometry::Point<float>& pos) const;

		bool isFirstUpdate;
	};
}
