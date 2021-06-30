#pragma once
#include "Piece.h"
#include <list>
#include <random>
#ifndef GUARD
#define GUARD
#include <SFML/Graphics.hpp>
using namespace sf;
#endif
//field can be generated with any size
class Field : public Drawable
{
public:
	Field();
	Field(Vector2f, int, int);
	Field(Field&);
	~Field();

	virtual void Update(std::list<Keyboard::Key>&) = 0;
	virtual void Refresh() = 0;
	virtual bool GameOver() = 0;
protected:
	int xSize;
	int ySize;
	const Color free = Block().getFillColor();
	Vector2f pos;
	RectangleShape frame;//frame of field
	Block** field;//all field blocks

	void Occupie(Piece&);
	virtual void draw(RenderTarget&, RenderStates) const;
	virtual int Check() = 0;
	Vector2i getIndexByVector(Vector2f) const;
};