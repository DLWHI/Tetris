#pragma once
#include <BlockBuilding/Piece.h>
#ifndef  GUARD
#define GUARD
#include <SFML/Graphics.hpp>
using namespace sf;
#endif
class FramedPiece : public Drawable
{
public:
	FramedPiece() = default;
	FramedPiece(Vector2f);
	FramedPiece(FramedPiece&);
	~FramedPiece();

	void capturePiece(const Piece*);
	void setPos(Vector2f&);
private:
	const Piece *piece = nullptr;
	RectangleShape frame;
	RectangleShape fader;

	virtual void draw(RenderTarget& taget, RenderStates states) const;
};