#include "EngineDebug.hpp"

#include <iostream>

using namespace Util;

EngineDebug::EngineDebug(King::Engine& engine) :
	engine(engine)
{
	
}

EngineDebug::~EngineDebug()
{

}

void EngineDebug::Write(const char * text, float x, float y, float rotation)
{
#ifdef DEBUG_LOG
	engine.Write(text, x, y, rotation);
#endif
}
