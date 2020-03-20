#include "IRenderer.hpp"

using namespace Render;

IRenderer::IRenderer() :
	engine(nullptr)
{
}

IRenderer::~IRenderer()
{
}

void IRenderer::setEngine(King::Engine* value)
{
	engine = value;
}
