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

	if (x != myX && y != myY) // No diagonal
		return false;

	int dirX = 0;
	int dirY = 0;

	if (x != myX) // Move on X axis
	{
		dirX = (myX - x > 0) ? -1 : 1; // Moving on the right: 1 - 3 = -2 so dir=1
	}
	else // Move on Y axis
	{
		dirY = (myY - y > 0) ? -1 : 1; // Moving on the right: 1 - 3 = -2 so dir=1
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