#include "pch.h"

Queen::Queen()
{
	name = "Queen";
	icon = 'Q';
}
Queen::~Queen() {}

bool Queen::CanMoveTo(Board* board, int x, int y) {
	return true;
}