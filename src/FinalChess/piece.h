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

	bool selected = false;

	BoardCase* cell;

	char getCorrectIcon();

	Piece();
	~Piece();

	void select();
	void unselect();

	virtual bool CanMoveTo(Board* board, int x, int y);
	
#ifdef SFML_STATIC
	sf::Texture* texture;
	sf::Sprite* sprite;

	int mouse_x;
	int mouse_y;

	virtual void initSprite();	
	void draw(sf::RenderWindow* window);
#endif
};