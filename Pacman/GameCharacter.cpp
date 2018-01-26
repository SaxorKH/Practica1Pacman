#include "GameCharacter.h"
#include "Game.h"
#include "FileFormatError.h"
#include "checkML.h"


GameCharacter::GameCharacter()
{
}

GameCharacter::GameCharacter(Game * g): PacManObject(g)
{
}
GameCharacter::GameCharacter(Game * g, unsigned int col) : PacManObject(g)
{
	texture = g->getTexture(CharacterTexture);
	spriteCol = col;
}
GameCharacter::GameCharacter(Game * g, unsigned int col, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir) : PacManObject(g)
{
	texture = g->getTexture(CharacterTexture);
	spriteCol = col;
	this->inix = inix;
	this->iniy = iniy;
	this->x = x;
	this->y = y;
	this->dir = dir;
}


GameCharacter::~GameCharacter()
{
}
void GameCharacter::render()
{
	SDL_Rect destRect = calcDestRect();
	anim = int(((SDL_GetTicks() / FRAME_RATE) % 2));
	Direction auxDir;
	if (dir == None)
		auxDir = Right;
	else auxDir = dir;
	texture->renderFrame(game->getRenderer(), destRect, auxDir, spriteCol * 2 + anim);
}
void GameCharacter::update()
{
	game->collision(*this);
}
void GameCharacter::loadFromFile(istream &archivo)
{
	archivo >> x;
	if (x < 0 || x >= game->getCols())
		throw FileFormatError("x imposible.");
	if (archivo.eof())
		throw FileFormatError("Falta información de personaje");
	archivo >> y;
	if (y < 0 || x >= game->getRows())
		throw FileFormatError("y imposible.");
	if (archivo.eof())
		throw FileFormatError("Falta información de personaje");
	archivo >> inix;
	if (inix < 0 || inix >= game->getCols())
		throw FileFormatError("x inicial imposible.");
	if (archivo.eof())
		throw FileFormatError("Falta información de personaje");
	archivo >> iniy;
	if (iniy < 0 || iniy >= game->getCols())
		throw FileFormatError("y inicial imposible.");
	if (archivo.eof())
		throw FileFormatError("Falta información de personaje");
	unsigned int aux;
	archivo >> aux;
	if (aux > 4)
		throw FileFormatError("Dirección imposible");
	dir = (Direction) aux;
}
void GameCharacter::saveToFile(ostream&archivo)
{
	archivo << x << " " << y << " " << inix << " " << iniy << " " << (unsigned int)dir << " ";
}
void GameCharacter::setTexture(Texture * t)
{
	texture = t;
}
int GameCharacter::getX()
{
	return x;
}
int GameCharacter::getY()
{
	return y;
}
int GameCharacter::getIniX()
{
	return inix;
}
int GameCharacter::getIniY()
{
	return iniy;
}
void GameCharacter::forward()
{
	if (dir == 0)
		x = (x + 1) % game->getCols();
	else if (dir == 1)
		y = (y + 1) % game->getRows();
	else if (dir == 2) {
		if (x == 0)
			x = game->getCols();
		x--;
	}
	else if (dir == 3) {
		if (y == 0)
			y = game->getRows();
		y--;
	}
}
SDL_Rect GameCharacter::calcDestRect()
{
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	destRect.w = destRect.h = cellSize;
	destRect.x = x * cellSize;
	destRect.y = y * cellSize;
	return destRect;
}
Direction GameCharacter::getDir()
{
	return dir;
}
