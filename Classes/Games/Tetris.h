#pragma once
#include "BlockBasic.h"
class Tetris : public Field
{
public:
	Tetris(Vector2f);
	
	Piece& getNext();
	Piece& getHeld();
	int& getScore();
	int& getLevel();

	virtual void Update(std::list<Keyboard::Key>&);
	virtual void Refresh();
	virtual bool GameOver();
protected:
	int score = 0;
	int lvl = 1;
	float time = 0;
	float delay = 0.5;
	bool pause = false;
	Clock timer;
	PieceInitter piecePool;
	Piece active;
	Piece next;
	Piece held;
	std::mt19937 gen;
	std::uniform_int_distribution<int> uidI;

	void setNewPiece();
	void setHeldPiece();
	void ClearLine(int);//cleares full lines
	void RotateActive();//checks if piece can freely rotate in its current pos, if cannot moves it so it could rotate
	void InputHandle(std::list<Keyboard::Key>&);
	virtual void draw(RenderTarget&, RenderStates) const;
	virtual int Check();
	int lineToScore(int);
	bool MoveCheck(Vector2i);//checks if piece can move by some vector
};