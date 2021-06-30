#pragma once
#include "Block.h"
#include "PosMatrix.h"
#ifndef GUARD
#define GUARD
#include <SFML/Graphics.hpp>
using namespace sf;
#endif
class Piece;
//piece class holds info about piece
namespace std { void swap(Piece&, Piece&); }
class Piece : public Drawable
{
public:
	Piece();
	Piece(Vector2f, PieceInfo&);
	Piece(const Piece&);
	~Piece();
	Block getBlock(int) const;//get special numered block from blocks array
	int getBlockCount() const;//get all block count
	//move shit
	void Move(Vector2f);
	void setPos(Vector2f);//set pos of piece
	void Rotate();//rotation around its center
	void Reset();//reset piece if something goes wrong
	friend void std::swap(Piece&, Piece&);
	Vector2f getPos();
	Vector2f findCenter() const;
private:
	int blockCount = 0;//default block count is zero so no piece treat would go
	std::string name;
	Block* blocks;//all the blocks we have
	//usually default tetris pieces have 4 blocks but if sick af and want to make one more piece we could do it with no problem by using dynamic array
	Vector2f pos;
	Vector2f* posMatrix;
	Vector2f pivot;//the rotation pivot of piece

	virtual void draw(RenderTarget&, RenderStates) const;
};