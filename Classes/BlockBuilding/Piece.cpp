#include "Piece.h"
Piece::Piece()
{
	this->blockCount = 0;
	this->posMatrix = new Vector2f[0];
	this->pos = Vector2f(0, 0);
	this->pivot = Vector2f(0, 0);
	blocks = new Block[0];
	name = "";
}
Piece::Piece(Vector2f startPos, PieceInfo& info)
{
	blockCount = info.getCount();
	posMatrix = new Vector2f[blockCount];
	for (int i = 0; i < blockCount; i++)
		posMatrix[i] = info.getBlockPos()[i];
	pos = startPos;
	pivot = info.getPivot();
	name = info.getName();
	blocks = new Block[blockCount];
	for (int i = 0; i < blockCount; i++) 
	{
		blocks[i].setFillColor(info.getColor());
		blocks[i].setPosition(startPos + posMatrix[i]*Block::size);
	}
}
Piece::Piece(const Piece& other)
{
	blockCount = other.blockCount;
	pos = other.pos;
	pivot = other.pivot;
	posMatrix = new Vector2f[blockCount];
	name = other.name;
	for (int i = 0; i < blockCount; i++)
		posMatrix[i] = other.posMatrix[i];
	blocks = new Block[blockCount];
	for (int i = 0; i < blockCount; i++)
		blocks[i] = other.blocks[i];
}
Piece::~Piece() 
{
	delete[] posMatrix;
	delete[] blocks;
}

Block Piece::getBlock(int n) const
{
	if (n >= blockCount || n < 0)
		throw new std::exception("Out of block array");
	return blocks[n];
} 
int Piece::getBlockCount() const
{
	return blockCount;
}
//move shit
void Piece::Move(Vector2f disp)
{
	for (int i = 0; i < blockCount; i++)
		blocks[i].move(disp);
	pos += disp;
}
void Piece::setPos(Vector2f pos)
{
	for (int i = 0; i < blockCount; i++)
		blocks[i].setPosition(pos +posMatrix[i]*Block::size);
	this->pos = pos;
}
void Piece::Rotate()
{
	for (int i = 0; i < blockCount; i++)
	{
		posMatrix[i] += pivot;
		std::swap(posMatrix[i].x, posMatrix[i].y);
		posMatrix[i].x *= -1.0;
		posMatrix[i] -= pivot;
	}
	Reset();
}
void Piece::Reset()
{
	for (int i = 0; i < blockCount; i++)
		blocks[i].setPosition(pos + posMatrix[i] * Block::size);
}
Vector2f Piece::getPos()
{
	return pos;
}
Vector2f Piece::findCenter() const 
{
	Vector2f sum(0, 0);
	for (int i = 0; i < blockCount; i++)
		sum += posMatrix[i];
	return sum / (float)blockCount;
}

void Piece::draw(RenderTarget& target, RenderStates states) const
{
	for (int i = 0; i < blockCount; i++)
		target.draw(blocks[i]);
}

void std::swap(Piece& a, Piece& b)
{
	std::swap(a.blockCount, b.blockCount);
	std::swap(a.blocks, b.blocks);
	std::swap(a.pos, b.pos);
	std::swap(a.posMatrix, b.posMatrix);
	std::swap(a.name, b.name);
	std::swap(a.pivot, b.pivot);
}