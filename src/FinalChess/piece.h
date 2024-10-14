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
	
#ifdef SFML_STATIC
	sf::Texture* texture;
	sf::Sprite* sprite;

	bool selected = false;

	int mouse_x;
	int mouse_y;

	void select();
	void unselect();

	virtual void initSprite();	
	void draw(sf::RenderWindow* window);
#endif
};