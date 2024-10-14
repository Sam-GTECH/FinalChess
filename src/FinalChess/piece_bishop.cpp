#include "pch.h"

Bishop::Bishop()
{
	name = "Bishop";
	icon = 'B';
}
Bishop::~Bishop() {}

bool Bishop::CanMoveTo(Board* board, int x, int y) {
	int myX = board->getPieceX(this);
	int myY = board->getPieceY(this);

	if (board->getCase(x, y)->getPiece()->is_white == is_white)
		return false;

	if (abs(myX - x) != abs(myY - y))
		return false;

	int dirX = (myX - x > 0) ? -1 : 1;
	int dirY = (myY - y > 0) ? -1 : 1;

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