#include "Ghost.h"
#include "Game.h"
#include <cstdlib>
using namespace std;

std::uniform_int_distribution<int> Ghost::distribution(0,3);
std::default_random_engine Ghost::generator;

Ghost::Ghost()
{
}

Ghost::Ghost(unsigned int color, Game * g, Texture * t) : GameCharacter(g, t, color)
{
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
	unsigned int vulColor = int(((SDL_GetTicks() / (FRAME_RATE * 2)) % 2));
	switch (state) {
	case 0:
		texture->renderFrame(game->getRenderer(), destRect, dir, spriteCol * 2 + anim);
		break;
	case 1:
		texture->renderFrame(game->getRenderer(), destRect, vulColor, 12 + anim);
		break;
	case 2:
		texture->renderFrame(game->getRenderer(), destRect, 2, 12 + anim);
		break;
	}
}

void Ghost::update()
{
	unsigned int frameTime;
	switch (state) {
	case 1:
		frameTime = SDL_GetTicks() - startVulTime;
		if (vulTime < frameTime)
			state = 0;
		break;
	case 2:
		frameTime = SDL_GetTicks() - startDeadTime;
		if (deadTime < frameTime) {
			state = 0;
			x = inix;
			y = iniy;
		}
	}

	Direction auxDir;
	bool elegido = false;

	do {
		unsigned int random = rand() % 4;
		auxDir = (Direction) random;
		switch (auxDir)
		{
		case Right:
			if (dir != 2 && game->nextCell(x, y, auxDir)) {
				dir = auxDir;
				elegido = true;
			}
			break;
		case Down:
			if (dir != 3 && game->nextCell(x, y, auxDir)) {
				dir = auxDir;
				elegido = true;
			}
			break;
		case Left:
			if (dir != 0 && game->nextCell(x, y, auxDir)) {
				dir = auxDir;
				elegido = true;
			}
			break;
		case 3:
			if (dir != 1 && game->nextCell(x, y, auxDir)) {
				dir = auxDir;
				elegido = true;
			}
			break;
		}
	} while (!elegido);
	forward();
}

void Ghost::vulnerable()
{
	if (state != 2) {
		state = 1;
		startVulTime = SDL_GetTicks();
	}
}

void Ghost::die()
{
	state = 2;
	startDeadTime = SDL_GetTicks();
}

unsigned int Ghost::getState()
{
	return state;
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