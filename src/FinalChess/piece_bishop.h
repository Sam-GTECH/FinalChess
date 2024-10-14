#pragma once

class Bishop : public Piece
{
public:

	Bishop();
	~Bishop();

	bool CanMoveTo(Board* board, int x, int y) override;
};