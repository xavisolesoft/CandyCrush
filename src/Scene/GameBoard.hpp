#pragma once

#include <vector>
#include <memory>

#include "Cell.hpp"
#include "../Geometry/BBox.hpp"
#include "../Geometry/Point.hpp"

namespace Gem
{
	class GemObject;
}

namespace Scene {
	class GameBoard
	{
	public:
		GameBoard();

		Geometry::BBox getBBox() const;
		Geometry::BBox getCellBBox(int x, int y) const;

		int getNumXCells() const;
		int getNumYCells() const;
		void setNumCells(int numXCells, int numYCells);

		void setCellWidth(float value);
		float getCellWidth() const;

		void setCellHeight(float value);
		float getCellHeight() const;

		void setTopLeft(const Geometry::Point& point);

		void setGemToCell(int x, int y, std::shared_ptr<Gem::GemObject> gem);
		std::shared_ptr<Gem::GemObject> getGemFromCell(int x, int y) const;
		void swap(std::shared_ptr<Gem::GemObject> gem1, std::shared_ptr<Gem::GemObject> gem2);
		void swap(int xCell1, int yCell1, int xCell2, int yCell2);

		void calculateBBoxes();

		const Cell* getCellFromWorldPos(float xWorld, float yWorld) const;

		bool isValidCell(int i, int j) const;
		bool isAnyCellEmpty() const;
		bool isAnyGemAnimated() const;

	private:
		void calculateSceneBBox();
		void calculateCellBox(int i, int j);


		std::vector<std::vector<Cell> > cells;
		float cellWidth;
		float cellHeight;
		Geometry::Point topLeft;
		Geometry::BBox bBox;
	};
}