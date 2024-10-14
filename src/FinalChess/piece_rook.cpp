#include "pch.h"

Rook::Rook()
{
	name = "Rook";
	icon = 'R';
}
Rook::~Rook() {}

bool Rook::CanMoveTo(Board* board, int x, int y) {
	int myX = board->getPieceX(this);
	int myY = board->getPieceY(this);

	if (x != myX && y != myY)
		return false;

	if (board->getCase(x, y)->getPiece()->is_white == is_white)
		return;

	int dirX = 0;
	int dirY = 0;

	if (x != myX)
	{
		dirX = (myX - x > 0) ? -1 : 1;
	}
	else
	{
		dirY = (myY - y > 0) ? -1 : 1;
	}

	int currentX = myX + dirX;
	int currentY = myY + dirY;
	while (currentX != x || currentY != y)
	{
		if (board->getCase(currentX, currentY)->getPiece() != nullptr)
			return false;

		currentX += dirX;
		currentY += dirY;
	}

	return true;
}