#pragma once

#include <memory>
#include <atomic>

#include "GemObject.hpp"
#include "../Gem/GemRenderer.hpp"

namespace Render
{
	class RenderController;
}

namespace Gem {
	class GemGenerator
	{
	public:
		GemGenerator(Render::RenderController& renderController);

		std::shared_ptr<GemObject> createNextGem();

		void removeGem(std::shared_ptr<GemObject> gem);

	private:
		long genereateNextId();
		GemType generateNextGemType() const;

		std::atomic<long> nextGemId;
		Render::RenderController& renderController;
		GemRenderer gemRenderer;
	};
}
