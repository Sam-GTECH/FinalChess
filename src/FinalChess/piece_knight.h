#pragma once

class Knight : public Piece
{
public:

	Knight();
	~Knight();

	bool CanMoveTo(Board* board, int x, int y) override;
};