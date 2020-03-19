#pragma once

#include <memory>
#include <atomic>

#include "GemObject.hpp"

namespace Gem {
	class GemGenerator
	{
	public:
		GemGenerator();

		std::shared_ptr<GemObject> createNextGem();

	private:
		long genereateNextId();
		GemType generateNextGemType() const;

		std::atomic<long> nextGemId;
	};
}
