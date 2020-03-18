#pragma once

#include <memory>

#include "../Geometry/BBox.hpp"
#include "../Geometry/Point.hpp"

namespace Scene {
	class Gem;
	class Cell
	{
	public:
		Cell();

		const Geometry::BBox& getBBox() const;
		void setBBox(const Geometry::BBox& value);

		std::shared_ptr<Gem> getGem() const;
		void setGem(std::shared_ptr<Gem> value);

		void setXCell(int value);
		int getXCell() const;

		void setYCell(int value);
		int getYCell() const;

		Geometry::Point getBoardPos() const;

	private:
		int xCell;
		int yCell;
		std::shared_ptr<Gem> gem;
		Geometry::BBox bBox;
	};
}
