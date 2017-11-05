#include "Pacman.h"



Pacman::Pacman(Game* g, Texture* t)
{
	game = g;
	texture = t;
}


Pacman::~Pacman()
{
}

void Pacman::setPos(unsigned int row, unsigned int col) {
	inix = x = col;
	iniy = y = row;
}
void Pacman::Render() {
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	destRect.w = destRect.h = cellSize;
	destRect.x = x * cellSize;
	destRect.y = y * cellSize;
	texture->renderFrame(game->getRenderer,destRect,dir,11);
}
