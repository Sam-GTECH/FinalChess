#pragma once
#include <vector>
#include "piece.h"

class BoardCase
{
public:
	BoardCase();
	//BoardCase(int x, int y);

	int valid_move;

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

	Piece* getPiece();
	void setPiece(Piece* piece);
	void print(bool cursor_on);

	// SFML Version
#ifdef SFML_STATIC
	int getVisualX();
	int getVisualY();
#endif
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

	Piece* selected_piece;

	bool update();

#ifdef SFML_STATIC
	void createGame(HWND hWnd);
#else
	void createGame();
#endif

	BoardCase* getBoard();
	BoardCase* getCase(int x, int y);
	BoardCase* getCase(int pos);

	int getPieceX(Piece* p);
	int getPieceY(Piece* p);
	void printBoard();

	// SFML Version
#ifdef SFML_STATIC
	sf::Texture* texture;
	sf::Sprite* sprite;

	bool mouse_held;
	void mousePressed(int x, int y);
	void mouseHeld(int x, int y);
	void mouseReleased(int x, int y);

	int getBoardCoord(int coord);

	sf::RenderWindow* getWindow();
	HWND getHWND();
#endif

#ifdef LOG
	Logger* log;
#endif

private:
	BoardCase board[8*8];
#ifdef SFML_STATIC
	sf::RenderWindow* window;
	HWND hWnd;
#endif

	void generatePieces(bool is_white);
	std::pair<int, int> convertToCoord(int pos);
};