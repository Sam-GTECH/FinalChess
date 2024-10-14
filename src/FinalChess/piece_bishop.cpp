#include "pch.h"

Bishop::Bishop()
{
	name = "Bishop";
	icon = 'B';
}
Bishop::~Bishop() {}

bool Bishop::CanMoveTo(Board* board, int x, int y) {
	return true;
}