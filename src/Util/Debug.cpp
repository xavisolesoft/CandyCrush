#include "Debug.hpp"

#include <iostream>

using namespace Util;

Debug::Debug()
{
	
}

Debug::~Debug()
{
#ifdef DEBUG_LOG
	std::cerr << stream.str() << std::endl;
#endif
}
