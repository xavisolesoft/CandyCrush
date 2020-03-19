#pragma once

#include <list>

#include "Animation.hpp"

namespace Animation {
	class ComposedSequentialAnimation :
		public IAnimation
	{
	public:
		ComposedSequentialAnimation();
		~ComposedSequentialAnimation();

		void appendAnimation(IAnimation& animation);

		bool update() override;

	private:
		std::list<IAnimation*> animations;
	};
}
