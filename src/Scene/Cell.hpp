#pragma once

#include <memory>

#include "../Geometry/BBox.hpp"
#include "../Geometry/Point.hpp"

namespace Gem
{
	class GemObject;
}

namespace Scene {
	class Cell
	{
	public:
		Cell();

		const Geometry::BBox<float>& getBBox() const;
		void setBBox(const Geometry::BBox<float>& value);

		std::shared_ptr<Gem::GemObject> getGem() const;
		void setGem(std::shared_ptr<Gem::GemObject> value);

		void setXCell(int value);
		int getXCell() const;

		void setYCell(int value);
		int getYCell() const;

		Geometry::Point<int> getBoardPos() const;

	private:
		int xCell;
		int yCell;
		std::shared_ptr<Gem::GemObject> gem;
		Geometry::BBox<float> bBox;
	};
}
