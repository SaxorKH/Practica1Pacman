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


GameCharacter::~GameCharacter()
{
}

void GameCharacter::render()
{
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	destRect.w = destRect.h = cellSize;
	destRect.x = x * cellSize;
	destRect.y = y * cellSize;
	anim = int(((SDL_GetTicks() / FRAME_RATE) % 2));
	texture->renderFrame(game->getRenderer(), destRect, dir, spriteCol + anim);
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

void GameCharacter::saveToFile()
{
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
