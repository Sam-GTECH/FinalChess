#pragma once

class Rook : public Piece
{
public:
	Rook();
	~Rook();

	bool CanMoveTo(Board* board, int x, int y) override;
};