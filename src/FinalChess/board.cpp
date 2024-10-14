#include "pch.h"

#define PIECE_WHITE_COLOR (15 << 4 | 0)
#define PIECE_BLACK_COLOR (0 << 4 | 15)
#define DEFAULT_COLOR (0 << 4 | 15)

BoardCase::BoardCase()
{
	this->x = 0;
	this->y = 0;
	piece = nullptr;
}

void BoardCase::setX(int x)
{
	this->x = x;
}
void BoardCase::setY(int y)
{
	this->y = y;
}

int BoardCase::getX()
{
	return x;
}
int BoardCase::getY()
{
	return y;
}

int BoardCase::getVisualX()
{
	return OFFSET + 16 * SCALE * x;
}
int BoardCase::getVisualY()
{
	return OFFSET + 16 * SCALE * (y - 1);
}


Piece* BoardCase::getPiece()
{
	return piece;
}

void BoardCase::setPiece(Piece* p)
{
	if (piece == p) return;

	if (piece != nullptr)
		piece->cell = nullptr;

	piece = p;

	if (p != nullptr)
		p->cell = this;
}

void BoardCase::print(bool cursor_on)
{
	if (piece)
	{
		int color = piece->is_white ? PIECE_WHITE_COLOR : PIECE_BLACK_COLOR;
		if (cursor_on)
			color = piece->is_white ? PIECE_BLACK_COLOR : PIECE_WHITE_COLOR;
		SetConsoleTextAttribute(CONSOLE, color);
		std::cout << piece->getCorrectIcon();
	}
	else
	{
		SetConsoleTextAttribute(CONSOLE, cursor_on ? PIECE_WHITE_COLOR : PIECE_BLACK_COLOR);
		std::cout << "O";
	}
	SetConsoleTextAttribute(CONSOLE, DEFAULT_COLOR);
	cout << " ";
}

///////////////////////////////////////////////////

Board::Board()
{
	w = 8;
	h = 8;

	turn_count = 0;

	cursor_x = floor(w/2);
	cursor_y = h-1;
	
	int x = 0; int y = 0;
	for (size_t i = 0; i < w*h; i++)
	{
		board[i].setX(x);
		board[i].setY(y);
		x++;
		if (x >= w)
		{
			x = 0;
			y++;
		}
	}
}

Board::~Board()
{
	for (size_t i = 0; i < w*h; i++)
	{
		delete getCase(i)->getPiece();
	}
}

void Board::generatePieces(bool is_white)
{
	int startRow = is_white ? h-2 : 1;

	for (size_t x = 0; x < w; x++)
	{
		Pawn* p = new Pawn();
		p->is_white = is_white;
		getCase(x, startRow)->setPiece(p);
		p->initSprite();
	}


	int y = is_white ? h-1 : 0;
#ifndef _LITE
	Rook* r = new Rook();
#else
	Pawn* r = new Pawn();
#endif
	r->is_white = is_white;
	getCase(0, y)->setPiece(r);
	r->initSprite();
#ifndef _LITE
	Rook* r2 = new Rook();
#else
	Pawn* r2 = new Pawn();
#endif
	r2->is_white = is_white;
	getCase(w - 1, y)->setPiece(r2);
	r2->initSprite();

	Knight* k1 = new Knight();
	k1->is_white = is_white;
	getCase(1, y)->setPiece(k1);
	k1->initSprite();
	Knight* k2 = new Knight();
	k2->is_white = is_white;
	getCase(w - 2, y)->setPiece(k2);
	k2->initSprite();

#ifndef _LITE
	Bishop* b1 = new Bishop();
#else
	Pawn* b1 = new Pawn();
#endif
	b1->is_white = is_white;
	getCase(2, y)->setPiece(b1);
	b1->initSprite();
#ifndef _LITE
	Bishop* b2 = new Bishop();
#else
	Pawn* b2 = new Pawn();
#endif
	b2->is_white = is_white;
	getCase(w - 3, y)->setPiece(b2);
	b2->initSprite();

	King* k = new King();
	k->is_white = is_white;
	getCase(3, y)->setPiece(k);
	k->initSprite();
#ifndef _LITE
	Queen* q = new Queen();
#else
	Knight* q = new Knight();
#endif
	q->is_white = is_white;
	getCase(4, y)->setPiece(q);
	q->initSprite();
}

void Board::createGame(HWND hWnd)
{
	window = new sf::RenderWindow(hWnd);
	if (window == NULL)
		return;

	this->hWnd = hWnd;

	texture = new sf::Texture();
	if (!texture->loadFromFile("../../../res/board_plain_05.png"))
	{
		MessageBox(hWnd, L"Can't load board texture!", L"Error!", MB_ICONERROR);
	}

	sprite = new sf::Sprite(*texture);
	sprite->setScale(4, 4);

	generatePieces(false);
	generatePieces(true);

	selected_piece = nullptr;
}

BoardCase* Board::getBoard()
{
	return board;
}

BoardCase* Board::getCase(int x, int y)
{
#ifdef _DEBUG
	int value = y * w + x;
	int size = w * h;
#endif
	return &board[y * w + x];
}
BoardCase* Board::getCase(int pos)
{
	return &board[pos];
}

sf::RenderWindow* Board::getWindow()
{
	return window;
}

HWND Board::getHWND()
{
	return hWnd;
}

int Board::getPieceX(Piece* p)
{
	for (size_t i = 0; i < w*h; i++)
	{
		BoardCase* c = getCase(i);
		if (c->getPiece() == p)
			return c->getX();
	}
}

int Board::getPieceY(Piece* p)
{
	for (size_t i = 0; i < w * h; i++)
	{
		BoardCase* c = getCase(i);
		if (c->getPiece() == p)
			return c->getY();
	}
}

std::pair<int, int> Board::convertToCoord(int pos)
{
	int x = pos % w;
	int y = pos / h;
	return { x, y };
}

void Board::printBoard()
{
	system("cls");
	for (size_t i = 0; i < w * h; i++)
	{
		auto cursor_pos = convertToCoord(i);
		getCase(i)->print(cursor_pos.first == cursor_x && cursor_pos.second == cursor_y);
		if ((i+1)%w == 0 && i+1 < w*h)
		{
			std::cout << std::endl;
		}
	}
#ifdef LOG
	log->printHistory();
#endif
}

bool Board::update()
{
	bool run = true;
	bool redraw = true;

	getWindow()->draw(*sprite);
	for (int i = 0; i < w*h; i++)
	{
		Piece* p = board[i].getPiece();
		if (p != nullptr)
			board[i].getPiece()->draw(getWindow());
	}

/*	while (run)
	{
		if (redraw)
		{
			printBoard();
			redraw = false;
		}

		int old_x = cursor_x; int old_y = cursor_y;
		if (GetAsyncKeyState(VK_UP) & 0x01)
			cursor_y--;
		else if (GetAsyncKeyState(VK_DOWN) & 0x01)
			cursor_y++;
		else if (GetAsyncKeyState(VK_LEFT) & 0x01)
			cursor_x--;
		else if (GetAsyncKeyState(VK_RIGHT) & 0x01)
			cursor_x++;
		else if (GetAsyncKeyState(VK_RETURN) & 0x01)
			turn_count++;

#ifdef _DEMO
		if (turn_count >= 2)
		{
			cout << "If you want to continue playing, please pay with your soul!" << endl;
			continue;
		}
#endif

		if (old_x != cursor_x || old_y != cursor_y)
			redraw = true;
	}
	*/
	return false;
}

void Board::mousePressed(int x, int y)
{
	for (size_t i = 0; i < w*h; i++)
	{
		Piece* p = board[i].getPiece();
		if (p == nullptr)
			continue;

		int cX = board[i].getVisualX();
		int cY = board[i].getVisualY()+(16 * SCALE);

		int w = 16 * SCALE;
		int h = w;

		if (Utils::pointInRect(x, y, cX, cY, w, h))
		{
			p->mouse_x = x;
			p->mouse_y = y;
			p->select();
			selected_piece = p;
			break;
		}
	}
}

void Board::mouseHeld(int x, int y)
{
	if (selected_piece == nullptr) return;
	selected_piece->mouse_x = x;
	selected_piece->mouse_y = y;
}

void Board::mouseReleased(int x, int y)
{
	if (selected_piece == nullptr) return;
	selected_piece->unselect();
	selected_piece = nullptr;
}