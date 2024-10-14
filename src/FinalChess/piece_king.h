#pragma once

class King : public Piece
{
public:
	King();
	~King();

	bool CanMoveTo(Board* board, int x, int y) override;
};