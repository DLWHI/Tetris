#include "Block.h"
const float Block::size = 22;
Block::Block()
{
	setSize(Vector2f(size - 2, size - 2));
	setFillColor(Color(79, 79, 79));
	setOutlineColor(Color::Black);
	setOutlineThickness(2);
}

Block::Block(Color color) : Block()
{
	setFillColor(color);
}

Block::Block(const Block& other) : Block()
{
	setFillColor(other.getFillColor());
	setPosition(other.getPosition());
}
Block::~Block() 
{
	
}

Block& Block::operator= (const Block& other)
{
	setFillColor(other.getFillColor());
	setPosition(other.getPosition());
	return *this;
}
