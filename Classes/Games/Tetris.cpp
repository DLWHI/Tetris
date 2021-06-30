#include "Tetris.h"
Tetris::Tetris(Vector2f fieldPos) : Field(fieldPos - Vector2f(0, 1) * Block::size, 10, 21)
{
	frame.move(Vector2f(0, 1)*Block::size);
	frame.setSize(Vector2f(xSize, ySize - 1) * Block::size);
	gen.seed(clock());
	uidI = std::uniform_int_distribution<int>(2, 7);

	Vector2f pos = this->pos + Vector2f(uidI(gen) * Block::size, 0);
	//PieceInfo info = piecePool.getPiece("brick");
	PieceInfo info = piecePool.getNext();
	next.~Piece();
	new (&next) Piece(pos, info);
	setNewPiece();
}

Piece& Tetris::getNext()
{
	return next;
}
Piece& Tetris::getHeld()
{
	return held;
}
int& Tetris::getScore()
{
	return score;
}
int& Tetris::getLevel()
{
	return lvl;
}

void Tetris::Update(std::list<Keyboard::Key>& keys)
{
	InputHandle(keys);
	if(!pause)
		time += timer.restart().asSeconds();
	if (time > delay)
	{
		time = 0;
		if (MoveCheck(Vector2i(0, 1)))
			active.Move(Vector2f(0, 1)*Block::size);
		else
		{
			Occupie(active);
			score += lineToScore(Check());
			setNewPiece();
		}
		held.setPos(active.getPos());
	}
}
bool Tetris::GameOver() 
{
	for (int i = 0; i < xSize; i++)
		if (field[0][i].getFillColor() != free)
			return true;
	return false;
}
void Tetris::Refresh() 
{
	delete[] field;
	score = 0;
	gen.seed(clock());
	field = new Block * [ySize];
	for (int j = 0; j < ySize; j++)
	{
		field[j] = new Block[xSize];
		for (int i = 0; i < xSize; i++)
			field[j][i].setPosition(pos + Vector2f(i, j) * Block::size);
	}
}

void Tetris::setNewPiece()
{
	Vector2f pos = this->pos + Vector2f(uidI(gen) * Block::size, 0);
	//PieceInfo info = piecePool.getPiece("");
	PieceInfo info = piecePool.getNext();

	active.~Piece();
	new (&active) Piece(next);

	bool retry = false;
	do {
		next.~Piece();
		new (&next) Piece(pos, info);
		for (int i = 0; i < next.getBlockCount(); i++)
		{
			Vector2i ind = getIndexByVector(next.getBlock(i).getPosition());
			if (ind.x < 0 || ind.x >= xSize)
				continue;
			if (ind.y < 0 || ind.y >= ySize)
				continue;
			if (field[ind.y][ind.x].getFillColor() != free)
			{
				pos = this->pos + Vector2f(uidI(gen) * Block::size, 0);
				retry = true;
				break;
			}
			retry = false;
		}
	} while (retry);
}
void Tetris::setHeldPiece()
{
	std::swap(held, active);
	if (!active.getBlockCount())
		setNewPiece();
}
void Tetris::ClearLine(int line)
{
	delete[] field[line];
	field[line] = new Block[xSize];
	for (int i = 0; i < xSize; i++)
		field[line][i].setPosition(pos + Vector2f(i, line) * Block::size);
	for (int i = line; i > 0; i--)
		std::swap(field[i], field[i - 1]);
	for (int i = 0; i <= line; i++)
		for (int j = 0; j < xSize; j++)
			field[i][j].setPosition(pos + Vector2f(j, i) * Block::size);
}
void Tetris::RotateActive()
{
	//check if piece can rotate at its pos
	active.Rotate();//rotationg piece
	for (int i = 0; i < active.getBlockCount(); i++)
	{
		//index extract
		Vector2i ind = getIndexByVector(active.getBlock(i).getPosition());
		if (ind.y <= 0)//if any block of piece is on 0 line(that's one above the window) we exit so no checks will be performed(and no segmention fault)
			return;
		if (!(MoveCheck(Vector2i(0, -1)) || MoveCheck(Vector2i(1, 0)) || MoveCheck(Vector2i(-1, 0))))
		{
			//if we can't move, just rotate it 3 more times to be as it was
			active.Rotate();
			active.Rotate();
			active.Rotate();
		}
		if (ind.x >= xSize || (MoveCheck(Vector2i(-1, 0)) && field[ind.y][ind.x].getFillColor() != free))//if we hit the wall or block, we move it to opposite direction
			active.Move(Vector2f(-1, 0) * Block::size);
		else if (ind.x <= -1 || (MoveCheck(Vector2i(1, 0)) && field[ind.y][ind.x].getFillColor() != free))
			active.Move(Vector2f(1, 0) * Block::size);
		else if (ind.y >= ySize || (MoveCheck(Vector2i(0, -1)) && field[ind.y][ind.x].getFillColor() != free))//if we hit block or bottom, we move it up
			active.Move(Vector2f(0, -1) * Block::size);
	}//simple
}
void Tetris::InputHandle(std::list<Keyboard::Key>& keys)
{
	for (auto i = keys.begin(); i != keys.end(); i++)
	{
		if (*i == Keyboard::D && MoveCheck(Vector2i(1, 0)) && !pause)
			active.Move(Vector2f(1, 0) * Block::size);
		if (*i == Keyboard::A && MoveCheck(Vector2i(-1, 0)) && !pause)
			active.Move(Vector2f(-1, 0) * Block::size);
		if (*i == Keyboard::S && !pause)
			time = delay;
		if (*i == Keyboard::W && !pause)
			RotateActive();
		if (*i == Keyboard::Space && !pause)
			setHeldPiece();
		if (*i == Keyboard::P)
			pause = pause xor true;
	}
	keys.clear();
}
void Tetris::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(frame);
	for (int j = 1; j < ySize; j++)
		for (int i = 0; i < xSize; i++)
			target.draw(field[j][i]);
	for(int i = 0; i < active.getBlockCount(); i++)
		if(active.getBlock(i).getPosition().y - Block::size >= pos.y)
		target.draw(active.getBlock(i));
}
int Tetris::Check()
{
	int cleared = 0;
	for (int i = ySize - 1; i >= 0; i--)
	{
		int j = 0;
		for (j = 0; j < xSize; j++)
			if (field[i][j].getFillColor() == free)
				break;
		if (j == xSize)
		{
			ClearLine(i);
			cleared++;
			i++;
		}
	}
	return cleared;
}
int Tetris::lineToScore(int lines)
{
	switch (lines)
	{
	case 1:
		return 100;
	case 2:
		return 300;
	case 3:
		return 700;
	case 4:
		return 1500;
	default:
		break;
	}
}
bool Tetris::MoveCheck(Vector2i displacement)
{
	for (int i = 0; i < active.getBlockCount(); i++)
	{
		Vector2i ind = getIndexByVector(active.getBlock(i).getPosition()) + displacement;
		if (ind.x < 0 || ind.x >= xSize)
			return false;
		if (ind.y < 0 || ind.y >= ySize)
			return false;
		if (field[ind.y][ind.x].getFillColor() != free)
			return false;
	}
	return true;
}
