#include "pch.h"

Piece::Piece()
{
	icon = 'O';
}
Piece::~Piece() {}

char Piece::getCorrectIcon()
{
	if (!is_white)
		return std::tolower(icon);
	return std::toupper(icon);
}

bool Piece::CanMoveTo(Board* board, int x, int y)
{ 
#ifdef LOG
	board->log->Warn("Default CanMoveTo function called!");
#endif
	return true;
}