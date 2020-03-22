#pragma once

#include <memory>

#include "GameLogic/LineMatcher.hpp"

namespace GameBoard
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
		PlayerActions(GameBoard::Board& gameBoard);

		void update(bool mouseButtonDown, float mouseX, float mouseY);

	private:
		void updateDragStart(const GameBoard::Cell* currentCell);
		void updateDragMove(const GameBoard::Cell* currentCell);
		void updateDragEnd(const GameBoard::Cell* currentCell);

		void trySwapGems(const GameBoard::Cell& cell1, const GameBoard::Cell& cell2);

		static void setSwapAnimations(std::shared_ptr<Gem::GemObject> gem1, std::shared_ptr<Gem::GemObject> gem2);
		static void appendSwapReturnAnimations(std::shared_ptr<Gem::GemObject> gem1, std::shared_ptr<Gem::GemObject> gem2);

		static bool isAllowedMovement(const GameBoard::Cell* originCell, const GameBoard::Cell* destinationCell);
		bool isDragStart(bool mouseButtonDown) const;
		bool isDragMove(bool mouseButtonDown) const;
		bool isDragEnd(bool mouseButtonDown) const;

		GameBoard::Board& gameBoard;
		LineMatcher lineMatcher;
		const GameBoard::Cell* selectedCell;
		std::weak_ptr<Gem::GemObject> prevSelectedGem;
		bool prevMouseButtonDown;
		const GameBoard::Cell* dragStartCell;
		bool dragAborted;

		static const float SWAP_SPEED;
	};
}
