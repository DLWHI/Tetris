#pragma once
#ifndef GUARD
#define GUARD
#include <SFML/Graphics.hpp>
using namespace sf;
#endif
//unit piece in this game, field and pieces are built with block with info
//it inherits SFML.RectangleShape class to be a little bit convinient to draw and move it 
class Block: public RectangleShape
{
public:
	Block();//default constructor
	Block(Color);//constructor
	Block(const Block&);//copy constructor
	~Block();
	Block& operator=(const Block&);//logic of block assignment
	static const float size;//size of block+outline, its convinient
};