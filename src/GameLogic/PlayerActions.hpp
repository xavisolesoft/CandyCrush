#pragma once

namespace Scene
{
	class GameBoard;
	class Cell;
}


namespace GameLogic {
	class LineMatcher;

	class PlayerActions
	{
	public:
		PlayerActions(Scene::GameBoard& gameBoard, const LineMatcher& lineMatcher);

		void update(bool mouseButtonDown, float mouseX, float mouseY);

	private:
		void updateDragStart(float mouseX, float mouseY);
		void updateDragMove(float mouseX, float mouseY);
		void updateDragEnd(float mouseX, float mouseY);

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
