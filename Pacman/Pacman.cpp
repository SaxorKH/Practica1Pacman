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
	destRect.x = x; destRect.y = y;
	texture->renderFrame(game->renderer,destRect,dir,11);
}
