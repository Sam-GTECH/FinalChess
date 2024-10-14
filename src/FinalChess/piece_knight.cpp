#include "pch.h"

Knight::Knight()
{
	name = "Knight";
	icon = 'K';
}
Knight::~Knight() {}

bool Knight::CanMoveTo(Board* board, int x, int y) {
	int myX = board->getPieceX(this);
	int myY = board->getPieceY(this);

	if (board->getCase(x, y)->getPiece() != nullptr && board->getCase(x, y)->getPiece()->is_white == is_white)
		return false;

	return  (abs(myX - x) == 2 && abs(myY - y) == 1) ||
			(abs(myX - x) == 1 && abs(myY - y) == 2);
}