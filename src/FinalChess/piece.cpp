#include "pch.h"

Piece::Piece()
{
	icon = 'O';
	cell = nullptr;
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

#ifdef SFML_STATIC
void Piece::select()
{
	selected = true;
	sprite->setColor(sf::Color::Green);
}

void Piece::unselect()
{
	selected = false;
	sprite->setColor(sf::Color::White);
}

void Piece::initSprite()
{
	sprite = new sf::Sprite();
	texture = new sf::Texture();

	char color = is_white ? 'W' : 'B';
	std::string path = "../../../res/" + std::string(1, color) + '_' + name + ".png";
	if (!texture->loadFromFile(path))
	{
		sf::err() << "Error occured loading texture at path: " << path << endl;
		return;
	}

	sprite->setTexture(*texture);
	sprite->setOrigin(0.5, 1);
	sprite->setScale(4, 4);
}

void Piece::draw(sf::RenderWindow* window)
{
	if (!cell) return;
	if (selected)
		sprite->setPosition(mouse_x, mouse_y);
	else
		sprite->setPosition(cell->getVisualX(), cell->getVisualY());
	window->draw(*sprite);
}
#endif