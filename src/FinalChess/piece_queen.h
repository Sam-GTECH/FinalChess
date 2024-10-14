#pragma once

class Queen : public Piece
{
public:
	Queen();
	~Queen();

	bool CanMoveTo(Board* board, int x, int y) override;
};