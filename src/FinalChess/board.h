#pragma once
#include <vector>
#include "piece.h"

class BoardCase
{
public:
	BoardCase();
	//BoardCase(int x, int y);

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	int getVisualX();
	int getVisualY();


	Piece* getPiece();
	void setPiece(Piece* piece);
	void print(bool cursor_on);
private:
	int x;
	int y;
	Piece* piece;
};

class Board
{
public:
	Board();
	~Board();

	int w;
	int h;

	int turn_count;

	int cursor_x;
	int cursor_y;

	sf::Texture* texture;
	sf::Sprite* sprite;

	bool update();

	void createGame(HWND hWnd);

	BoardCase* getBoard();
	BoardCase* getCase(int x, int y);
	BoardCase* getCase(int pos);
	sf::RenderWindow* getWindow();
	HWND getHWND();

	int getPieceX(Piece* p);
	int getPieceY(Piece* p);
	void printBoard();

#ifdef LOG
	Logger* log;
#endif

private:
	BoardCase board[8*8];
	sf::RenderWindow* window;
	HWND hWnd;

	void generatePieces(bool is_white);
	std::pair<int, int> convertToCoord(int pos);
};