#pragma once

#include <memory>
#include <cstdlib>
#include <atomic>

#include "Gem.hpp"

namespace Scene {
	class GemGenerator
	{
	public:
		GemGenerator();

		std::shared_ptr<Gem> createNextGem();

	private:
		long genereateNextId();
		GemType generateNextGemType() const;

		std::atomic<long> nextGemId;
	};
}
