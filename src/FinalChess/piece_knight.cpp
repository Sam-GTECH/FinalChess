#include "pch.h"

Knight::Knight()
{
	name = "Knight";
	icon = 'K';
}
Knight::~Knight() {}

bool Knight::CanMoveTo(Board* board, int x, int y) {
	return true;
}