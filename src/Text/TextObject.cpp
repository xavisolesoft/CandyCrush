#include "TextObject.hpp"

using namespace Text;

TextObject::TextObject(long id) :
	IGameObject(id)
{

}

void TextObject::setText(std::string value)
{
	text = std::move(value);
}

const std::string& TextObject::getText() const
{
	return text;
}
