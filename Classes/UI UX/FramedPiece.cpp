#include "FramedPiece.h"
FramedPiece::FramedPiece(Vector2f pos)
{
	Vector2f frameSize(5, 5);
	frameSize *= Block::size;

	frame.setPosition(pos);
	frame.setSize(frameSize);
	frame.setFillColor(Color(0, 0, 0, 0));
	frame.setOutlineColor(Color(35, 35, 35));
	frame.setOutlineThickness(4);

	fader.setPosition(pos);
	fader.setSize(frameSize);
	fader.setFillColor(Color(0, 0, 0, 1));
	fader.setOutlineColor(Color(0, 0, 0));
	fader.setOutlineThickness(Block::size);
}
FramedPiece::FramedPiece(FramedPiece& other)
{
	piece = other.piece;
	frame = other.frame;
}
FramedPiece::~FramedPiece()
{

}

void FramedPiece::capturePiece(const Piece* piece) 
{
	this->piece = piece;
}
void FramedPiece::setPos(Vector2f& pos) 
{
	frame.setPosition(pos);
	fader.setPosition(pos);
}

void FramedPiece::draw(RenderTarget& target, RenderStates states) const 
{
	if (piece != nullptr) 
	{
		Piece ghost(*piece);
		Vector2f frameCenter = frame.getPosition() + Vector2f(4, 4) * Block::size / 2.0f;
		Vector2f pieceCenter = ghost.findCenter();
		ghost.setPos(frameCenter - pieceCenter * Block::size);

		Rect hitbox(frame.getPosition() - Vector2f(1, 1) * Block::size, frame.getSize() + Vector2f(1, 1) * Block::size);
		if (ghost.getBlockCount() == 4)
			target.draw(ghost);
		else
			for (int i = 0; i < ghost.getBlockCount(); i++)
				if (hitbox.contains(ghost.getBlock(i).getPosition()))
					target.draw(ghost.getBlock(i));
	}
	target.draw(fader);
	target.draw(frame);
}