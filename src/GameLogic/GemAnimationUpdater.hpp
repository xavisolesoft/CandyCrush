#pragma once

namespace Scene
{
	class GameBoard;
}

namespace GameLogic {
	class GemAnimationUpdater
	{
	public:
		GemAnimationUpdater();

		void update(Scene::GameBoard& gameBoard);
	};
}
