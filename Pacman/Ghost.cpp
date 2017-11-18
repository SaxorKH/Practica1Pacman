#include "Ghost.h"
#include "Game.h"


std::uniform_int_distribution<int> Ghost::distribution(0,3);
std::default_random_engine Ghost::generator;

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
	for (int i = 0; i < 10; i++)
		distribution(generator);
	do {
		dir = distribution(generator);
	} while (!game->nextCell(x, y, dir));
	forward();
}


void Ghost::forward()
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