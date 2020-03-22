#pragma once

#include "GameObject/IGameObject.hpp"

namespace Gem {
	enum class GemType
	{
		UNDEFINED,
		BLUE,
		GREEN,
		PURPLE,
		RED,
		YELLOW
	};

	class GemObject :
		public GameObject::IGameObject
	{
	public:
		GemObject(long id, GemType gemType);

		GemType getGemType() const;

	private:
		GemType gemType;
	};
}
