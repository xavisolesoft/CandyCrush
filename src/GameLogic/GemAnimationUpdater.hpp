#pragma once

namespace Scene
{
	class Board;
}

namespace GameLogic {
	class GemAnimationUpdater
	{
	public:
		GemAnimationUpdater();

		void update(Scene::Board& gameBoard);
	};
}
