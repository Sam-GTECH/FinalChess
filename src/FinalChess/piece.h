#pragma once
#include <string>

class Board;

class Piece
{
public:

	std::string name;
	char icon;

	bool is_white;

	char getCorrectIcon();

	Piece();
	~Piece();

	virtual bool CanMoveTo(Board* board, int x, int y);
};