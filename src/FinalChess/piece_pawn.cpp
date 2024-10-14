#include "pch.h"

Pawn::Pawn()
{
	name = "Pawn";
	icon = 'P';
}
Pawn::~Pawn() {}

bool Pawn::CanMoveTo(Board* board, int x, int y) {
	int myX = board->getPieceX(this);
	int myY = board->getPieceY(this);

	if (x != myX)
		return false;

	int dir = is_white ? 1 : -1;

	if (!moved_once)
	{
		moved_once = true;
		bool mouv_cond = y == myY + 1 * dir || y == myY + 2 * dir;
		bool occupied_cond = board->getCase(myX, myY + 1 * dir)->getPiece() == nullptr && board->getCase(myX, myY + 2 * dir)->getPiece() == nullptr;
		return mouv_cond && occupied_cond;
	}
	bool mouv_cond = y == myY + 1 * dir;
	bool occupied_cond = board->getCase(myX, myY + 1 * dir)->getPiece() == nullptr;
	return mouv_cond && occupied_cond;
}