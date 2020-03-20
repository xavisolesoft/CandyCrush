#pragma once

namespace Util{
template<class T>
class ISingleton
{
public:
	static T& getInstance()
	{
		static T instance;
		return instance;
	}
};
}
