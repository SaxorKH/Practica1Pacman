#include "Ghost.h"
#include "Game.h"
#include <cstdlib>
using namespace std;


bool Ghost::sinSalida(Direction nextDir)
{
	Direction dirUno, dirDos;
	if (nextDir == Right)
		dirUno = Up;
	else {
		unsigned int ui = nextDir-1;
		dirUno = (Direction) ui;
	}

	if (nextDir == Up)
		dirDos = Right;
	else {
		unsigned int ui = nextDir + 1;
		dirDos = (Direction) ui;
	}

	return !game->nextCell(x, y, dirUno) && !game->nextCell(x, y, nextDir) && !game->nextCell(x, y, dirDos);

}

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

	if (state == Alive || state == Adult)
		GameCharacter::render();
	else {
		SDL_Rect destRect;
		unsigned int cellSize = game->getCellSize();
		destRect.w = destRect.h = cellSize;
		destRect.x = x * cellSize;
		destRect.y = y * cellSize;
		anim = int(((SDL_GetTicks() / FRAME_RATE) % 2));
		if (state == Scared || state == Old) {
			unsigned int vulColor = int(((SDL_GetTicks() / (FRAME_RATE * 2)) % 2));
			texture->renderFrame(game->getRenderer(), destRect, vulColor, 12 + anim);
		}
		else
			texture->renderFrame(game->getRenderer(), destRect, 2, 12 + anim);
	}
}

void Ghost::update()
{
	unsigned int frameTime;
	switch (state) {
	case Scared:
		frameTime = SDL_GetTicks() - startVulTime;
		if (vulTime < frameTime)
			state = defaultState;
		break;
	case Dead:
		frameTime = SDL_GetTicks() - startDeadTime;
		if (deadTime < frameTime) {
			state = Alive;
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
			if (dir != Left && game->nextCell(x, y, auxDir)) {
				dir = auxDir;
				elegido = true;
			}
			else if (dir == Left && sinSalida(auxDir))
				elegido = true;

			break;
		case Down:
			if (dir != Up && game->nextCell(x, y, auxDir)) {
				dir = auxDir;
				elegido = true;
			}
			else if (dir == Up && sinSalida(auxDir))
				elegido = true;
			break;
		case Left:
			if (dir != Right && game->nextCell(x, y, auxDir)) {
				dir = auxDir;
				elegido = true;
			}
			else if (dir == Right && sinSalida(auxDir))
				elegido = true;
			break;
		case Up:
			if (dir != Down && game->nextCell(x, y, auxDir)) {
				dir = auxDir;
				elegido = true;
			}
			else if (dir == Down && sinSalida(auxDir))
				elegido = true;
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