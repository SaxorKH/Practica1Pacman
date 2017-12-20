#include "GameCharacter.h"
#include "Game.h"


GameCharacter::GameCharacter()
{

}

GameCharacter::GameCharacter(Game * g): GameObject(g)
{
}
GameCharacter::GameCharacter(Game * g, Texture * t, unsigned int col) : GameObject(g)
{
	texture = t;
	spriteCol = col;
}
GameCharacter::GameCharacter(Game * g, Texture * t, unsigned int col, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir) : GameObject(g)
{
	texture = t;
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
void GameCharacter::loadFromFile(istream &archivo)
{
	archivo >> x;
	archivo >> y;
	archivo >> inix;
	archivo >> iniy;
	unsigned int aux;
	archivo >> aux;
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
void GameCharacter::die()
{
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
