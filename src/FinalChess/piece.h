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
	
	sf::Texture* texture;
	sf::Sprite* sprite;

	bool selected = false;
	void select();
	void unselect();

	int mouse_x;
	int mouse_y;

	virtual void initSprite();	
	void draw(sf::RenderWindow* window);
};