#include "Field.h"
Field::Field()
{
	//constructor recieves size of field and its pos
	xSize = 0;
	ySize = 0;
	//field blocks init by default they're gray and not occupied
	field = new Block * [0];
}
Field::Field(Vector2f pos, int xSize, int ySize) 
{
	//constructor recieves size of field and its pos
	this->xSize = xSize;
	this->ySize = ySize;
	this->pos = pos;
	//frame init
	frame.setPosition(pos - Vector2f(1, 0));
	frame.setSize(Vector2f(xSize, ySize) * Block::size);
	frame.setFillColor(Color(35, 35, 35));
	frame.setOutlineColor(Color(35, 35, 35));
	frame.setOutlineThickness(4);
	//field blocks init by default they're gray and not occupied
	field = new Block*[ySize];
	for (int j = 0; j < ySize; j++)
	{
		field[j] = new Block[xSize];
		for (int i = 0; i < xSize; i++)
			field[j][i].setPosition(pos + Vector2f(i, j)* Block::size);
	}
}
Field::Field(Field& other)
{
	delete[] field;
	//constructor recieves size of field and its pos
	xSize = other.xSize;
	ySize = other.ySize;
	pos = other.pos;
	//frame init
	frame = other.frame;
	//field blocks init by default they're gray and not occupied
	field = new Block * [ySize];
	for (int j = 0; j < ySize; j++)
	{
		field[j] = new Block[xSize];
		for (int i = 0; i < xSize; i++) 
			field[j][i] = other.field[j][i];
	}
}
Field::~Field() 
{
	delete[] field;
}

void Field::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(frame);
	for (int j = 0; j < ySize; j++)
		for (int i = 0; i < xSize; i++)
			target.draw(field[j][i]);
}
void Field::Occupie(Piece& piece)
{
	for (int i = 0; i < piece.getBlockCount(); i++)
	{
		Vector2i ind = getIndexByVector(piece.getBlock(i).getPosition());
		if (ind.x < 0 || ind.x >= xSize)
			continue;
		if (ind.y < 0 || ind.y >= ySize)
			continue;
		field[ind.y][ind.x] = piece.getBlock(i);
	}
}

Vector2i Field::getIndexByVector(Vector2f vector) const 
{
	Vector2i res;
	res.x = round(vector.x - pos.x) / Block::size;
	res.y = round(vector.y - pos.y) / Block::size;
	return res;
}