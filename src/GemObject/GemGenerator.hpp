#pragma once

#include <memory>
#include <atomic>

#include "Gem.hpp"

namespace GemObject {
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
