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

	return (abs(x - myX) <= 1 && abs(y - myY) <= 1);
}