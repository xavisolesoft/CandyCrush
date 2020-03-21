#pragma once

#include <memory>

#include "../GameLogic/LineMatcher.hpp"

namespace Board
{
	class Board;
	class Cell;
}

namespace Gem
{
	class GemObject;
}


namespace GameLogic {
	class PlayerActions
	{
	public:
		PlayerActions(Board::Board& gameBoard);

		void update(bool mouseButtonDown, float mouseX, float mouseY);

	private:
		void updateDragStart(const Board::Cell* currentCell);
		void updateDragMove(const Board::Cell* currentCell);
		void updateDragEnd(const Board::Cell* currentCell);

		void trySwapGems(const Board::Cell& cell1, const Board::Cell& cell2);

		static void setSwapAnimations(std::shared_ptr<Gem::GemObject> gem1, std::shared_ptr<Gem::GemObject> gem2);
		static void appendSwapReturnAnimations(std::shared_ptr<Gem::GemObject> gem1, std::shared_ptr<Gem::GemObject> gem2);

		static bool isAllowedMovement(const Board::Cell* originCell, const Board::Cell* destinationCell);
		bool isDragStart(bool mouseButtonDown) const;
		bool isDragMove(bool mouseButtonDown) const;
		bool isDragEnd(bool mouseButtonDown) const;

		Board::Board& gameBoard;
		LineMatcher lineMatcher;
		const Board::Cell* selectedCell;
		bool prevMouseButtonDown;
		const Board::Cell* dragStartCell;
		bool dragAborted;
	};
}
