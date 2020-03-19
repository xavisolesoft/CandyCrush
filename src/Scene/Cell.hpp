#pragma once

#include <memory>

#include "../Geometry/BBox.hpp"
#include "../Geometry/Point.hpp"

namespace GemObject
{
	class Gem;
}

namespace Scene {
	class Cell
	{
	public:
		Cell();

		const Geometry::BBox& getBBox() const;
		void setBBox(const Geometry::BBox& value);

		std::shared_ptr<GemObject::Gem> getGem() const;
		void setGem(std::shared_ptr<GemObject::Gem> value);

		void setXCell(int value);
		int getXCell() const;

		void setYCell(int value);
		int getYCell() const;

		Geometry::Point getBoardPos() const;

	private:
		int xCell;
		int yCell;
		std::shared_ptr<GemObject::Gem> gem;
		Geometry::BBox bBox;
	};
}
