#include "pch.h"

King::King()
{
	name = "King";
	icon = 'K';
}
King::~King() {}

bool King::CanMoveTo(Board* board, int x, int y) {
	int myX = board->getPieceX(this);
	int myY = board->getPieceY(this);

	if (board->getCase(x, y)->getPiece()->is_white == is_white)
		return false;

	return (abs(x - myX) <= 1 && abs(y - myY) <= 1);
}