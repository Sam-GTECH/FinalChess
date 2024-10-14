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

	return true;
}