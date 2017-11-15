#include "Ghost.h"
#include "Game.h"



Ghost::Ghost()
{
}

Ghost::Ghost(unsigned int color, Game * g, Texture * t)
{
	this->color = color;
	game = g;
	texture = t;
}


Ghost::~Ghost()
{
}

void Ghost::setPos(unsigned int row, unsigned int col)
{
	inix = x = col;
	iniy = y = row;
}

void Ghost::render()
{
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	destRect.w = destRect.h = cellSize;
	destRect.x = x * cellSize;
	destRect.y = y * cellSize;
	anim = int(((SDL_GetTicks() / FRAME_RATE) % 2));
	texture->renderFrame(game->getRenderer(), destRect, dir, color*2 + anim);
}

void Ghost::update()
{
}


void Ghost::forward()
{
}