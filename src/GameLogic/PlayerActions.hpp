#pragma once

#include <memory>

namespace Scene
{
	class GameBoard;
	class Cell;
	class Gem;
}


namespace GameLogic {
	class LineMatcher;

	class PlayerActions
	{
	public:
		PlayerActions(Scene::GameBoard& gameBoard, const LineMatcher& lineMatcher);

		void update(bool mouseButtonDown, float mouseX, float mouseY);

	private:
		void updateDragStart(const Scene::Cell* currentCell);
		void updateDragMove(const Scene::Cell* currentCell);
		void updateDragEnd(const Scene::Cell* currentCell);

		static void setSwapAnimations(std::shared_ptr<Scene::Gem> gem1, std::shared_ptr<Scene::Gem> gem2);
		static void appendSwapReturnAnimations(std::shared_ptr<Scene::Gem> gem1, std::shared_ptr<Scene::Gem> gem2);

		static bool isAllowedMovement(const Scene::Cell* originCell, const Scene::Cell* destinationCell);
		bool isDragStart(bool mouseButtonDown) const;
		bool isDragMove(bool mouseButtonDown) const;
		bool isDragEnd(bool mouseButtonDown) const;

		Scene::GameBoard& gameBoard;
		const LineMatcher& lineMatcher;
		const Scene::Cell* selectedCell;
		bool prevMouseButtonDown;
		const Scene::Cell* dragStartCell;
		bool dragAborted;
	};
}
