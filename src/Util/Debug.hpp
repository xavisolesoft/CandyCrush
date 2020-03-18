#pragma once

#include <string>
#include <sstream>

namespace Util {
	class Debug
	{
	public:
		Debug();
		~Debug();
		
		template<class T>
		Debug &operator<<(const T &x) {
#ifdef DEBUG_LOG
			stream << x;
#endif
			return *this;
		}
		
	private:
		std::ostringstream stream;
	};
}
