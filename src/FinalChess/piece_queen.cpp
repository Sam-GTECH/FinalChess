﻿#include "pch.h"

Queen::Queen()
{
	name = "Queen";
	icon = 'Q';
}
Queen::~Queen() {}

bool Queen::CanMoveTo(Board* board, int x, int y) {
	int myX = board->getPieceX(this);
	int myY = board->getPieceY(this);

	if (board->getCase(x, y)->getPiece() != nullptr && board->getCase(x, y)->getPiece()->is_white == is_white)
		return false;

	bool diag_mode = (abs(myX - x) == abs(myY - y));

	int dirX;
	int dirY;
	if (diag_mode)
	{
		dirX = (myX - x > 0) ? -1 : 1;
		dirY = (myY - y > 0) ? -1 : 1;
	}
	else
	{
		dirX = 0;
		dirY = 0;

		if (x != myX)
		{
			dirX = (myX - x > 0) ? -1 : 1;
		}
		else
		{
			dirY = (myY - y > 0) ? -1 : 1;
		}
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