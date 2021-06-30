#include "FramedText.h"
FramedText::FramedText(Text text, Vector2f pos)
{
	txt = text;
	txt.setPosition(pos);

	frame.setPosition(pos);
	FloatRect bounds = txt.getLocalBounds();
	txt.move(Vector2f(-bounds.left, -bounds.top) + spacing);
	frame.setSize(Vector2f(bounds.width, bounds.height) + spacing*2.0f);
	frame.setFillColor(Color::Black);
	frame.setOutlineColor(Color::White);
	frame.setOutlineThickness(4);
}
FramedText::FramedText(Text text, Vector2f pos, bool fixed) : FramedText(text, pos)
{
	isFixed = fixed;
	Reset();
}
FramedText::FramedText(FramedText& other)
{
	txt = other.txt;
	frame = other.frame;
	spacing = other.spacing;
}
FramedText::~FramedText()
{

}

void FramedText::setPos(Vector2f pos)
{
	frame.setPosition(pos);
	Reset();
}
void FramedText::setSpacing(Vector2f spacing) 
{
	this->spacing = spacing;
	Reset();
}
void FramedText::setString(std::string str) 
{
	txt.setString(str);
	Reset();
}
void FramedText::setCharacterSize(unsigned int size)
{
	txt.setCharacterSize(size);
	Reset();
}
void FramedText::setOutlineThickness(unsigned int size)
{
	frame.setOutlineThickness(size);
}
void FramedText::setTextColor(Color color) 
{
	txt.setFillColor(color);
}
void FramedText::setFillColor(Color color) 
{
	frame.setFillColor(color);
}
void FramedText::setOutlineColor(Color color) 
{
	frame.setOutlineColor(color);
}
void FramedText::setState(bool state) 
{
	isFixed = state;
}

Vector2f FramedText::getPos() 
{
	return frame.getPosition();
}
Vector2f FramedText::getSpacing() 
{
	return spacing;
}
std::string FramedText::getString() 
{
	return txt.getString();
}
unsigned int FramedText::getCharacterSize() 
{
	return txt.getCharacterSize();
}
unsigned int FramedText::getOutlineThickness() 
{
	return frame.getOutlineThickness();
}
Color FramedText::getTextColor() 
{
	return txt.getFillColor();
}
Color FramedText::getFillColor() 
{
	return frame.getFillColor();
}
Color FramedText::getOutlineColor() 
{
	return frame.getOutlineColor();
}
bool FramedText::getState() 
{
	return isFixed;
}

void FramedText::Reset() 
{
	FloatRect bounds = txt.getLocalBounds();
	txt.setPosition(frame.getPosition());
	if (isFixed)
	{
		Vector2f center = frame.getSize() / 2.0f;
		unsigned int charSize = txt.getCharacterSize();
		while (bounds.width > 2 * center.x || bounds.height > 2 * center.y)
		{
			txt.setCharacterSize(--charSize);
			bounds = txt.getLocalBounds();
		}
		txt.move(center);
		txt.move(-Vector2f(bounds.width, bounds.height) / 2.0f);
		txt.move(-Vector2f(bounds.left, bounds.top));
	}
	else
	{
		frame.setSize(Vector2f(bounds.width, bounds.height) + spacing * 2.0f);
		txt.move(Vector2f(-bounds.left, -bounds.top) + spacing);
	}
}

void FramedText::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(frame);
	target.draw(txt);
}