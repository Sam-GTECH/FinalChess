#pragma once

class Board;

class Pawn : public Piece
{
public:
	bool moved_once = false;

	Pawn();
	~Pawn();

	bool CanMoveTo(Board* board, int x, int y) override;
};