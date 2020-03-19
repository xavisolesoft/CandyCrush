#pragma once

#include "../GameObject/IGameObject.hpp"

namespace Scene {
	enum class GemType
	{
		UNDEFINED,
		BLUE,
		GREEN,
		PURPLE,
		RED,
		YELLOW
	};

	class Gem :
		public GameObject::IGameObject
	{
	public:
		Gem(long id, GemType gemType);

		GemType getGemType() const;

	private:
		GemType gemType;
	};
}
