#pragma once

#include "../Scene/IScene.hpp"

namespace GameBoard
{
	class Board;
}

namespace Gem
{
	class GemGenerator;
}

namespace King
{
	class Engine;
}

namespace Scene {
	class EndGameScene :
		public IScene
	{
	public:
		EndGameScene();
		~EndGameScene();
		
		void start() override;
		void update() override;
		bool end() override;

	private:
		void createTheEndTextObject() const;
	};
}
