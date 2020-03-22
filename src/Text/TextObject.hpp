#pragma once

#include <string>

#include "GameObject/IGameObject.hpp"

namespace Text {
	class TextObject :
		public GameObject::IGameObject
	{
	public:
		TextObject(long id);

		void setText(std::string value);
		const std::string& getText() const;

	private:
		std::string text;
	};
}
