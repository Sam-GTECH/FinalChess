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

	if (board->getCase(x, y)->getPiece()->is_white == is_white)
		return;

	int dir = is_white ? -1 : 1;

	bool can_move = false;
	if (!moved_once)
	{
		moved_once = true;
		bool mouv_cond = y == myY + 1 * dir || y == myY + 2 * dir;
		bool occupied_cond = board->getCase(myX, myY + 1 * dir)->getPiece() == nullptr && board->getCase(myX, myY + 2 * dir)->getPiece() == nullptr;
		if (mouv_cond && occupied_cond) can_move = true;
	}
	else
	{
		bool mouv_cond = y == myY + 1 * dir;
		bool occupied_cond = board->getCase(myX, myY + 1 * dir)->getPiece() == nullptr;
		if (mouv_cond && occupied_cond) can_move = true;
	}
	if (can_move && !moved_once)
		moved_once = true;
	return can_move;
}