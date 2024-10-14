#pragma once
#include "pch.h"

class BoardCase;

class Board;

class Piece
{
public:

	std::string name;
	char icon;

	bool is_white;

	BoardCase* cell;

	char getCorrectIcon();

	Piece();
	~Piece();

	virtual bool CanMoveTo(Board* board, int x, int y);
	
	virtual void initSprite();
	sf::Texture* texture;
	sf::Sprite* sprite;
	void draw(sf::RenderWindow* window);
};