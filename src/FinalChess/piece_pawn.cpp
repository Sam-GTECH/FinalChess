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

	if (board->getCase(x, y)->getPiece() != nullptr && board->getCase(x, y)->getPiece()->is_white == is_white)
		return false;

	int dir = is_white ? -1 : 1;

	if (abs(myX - x) == 1 && y == myY + 1 * dir) {
		Piece* p = board->getCase(x, y)->getPiece();
		if (p != nullptr && p->is_white != is_white) {
			return true;
		}
	}

	if (x != myX)
		return false;

	if (y == myY + 1 * dir) {
		if (board->getCase(x, y)->getPiece() == nullptr) {
			return true;
		}
	}

	if (!moved_once && y == myY + 2 * dir) {
		if (board->getCase(myX, myY + 1 * dir)->getPiece() == nullptr &&
			board->getCase(myX, myY + 2 * dir)->getPiece() == nullptr) {
			return true;
		}
	}

	return false;
}