#include "Ghost.h"
#include "Game.h"
#include <cstdlib>
#include "checkML.h"
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

Ghost::Ghost(unsigned int color, Game * g) : GameCharacter(g, color)
{
}

Ghost::Ghost(Game * g, unsigned int col, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir) : GameCharacter(g, col, inix, iniy, x, y, dir)
{
}


Ghost::~Ghost()
{
}

void Ghost::render()
{

	if (state == Alive || state == Adult)
		GameCharacter::render();
	else {
		SDL_Rect destRect = calcDestRect();
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
		if (VUL_TIME < frameTime) {
			state = defaultState;
			startVulTime = SDL_GetTicks();
		}
		break;
	case Dead:
		frameTime = SDL_GetTicks() - startDeadTime;
		if (deadTime < frameTime) {
			state = Alive;
			x = inix;
			y = iniy;
			dir = None;
		}
	}

	Direction auxDir;
	bool elegido = false;
		do {
		unsigned int random = rand() % 4;
		auxDir = (Direction)random;
		if (dir == None)
			dir = auxDir;
		if ((auxDir != (dir + 2) % 4 && game->nextCell(x, y, auxDir)) || (auxDir == (dir + 2) % 4 && sinSalida(dir))) {
			dir = auxDir;
			elegido = true;
		}
	} while (!elegido);
	forward();
	if(state == Alive || state == Adult)
		GameCharacter::update();
}


void Ghost::saveToFile(ostream & archivo)
{
	archivo << 0 << " ";
	GameCharacter::saveToFile(archivo);
	archivo << endl;
}

void Ghost::scared(unsigned int energy)
{
	if (state != Dead && state != Old) {
		state = Scared;
		startVulTime = SDL_GetTicks() - energy;
		dir = (Direction)((dir + 2) % 4);
	}
}

void Ghost::die()
{
	state = Dead;
	startDeadTime = SDL_GetTicks();
	game->increasePoints(500);
}

GhostState Ghost::getState()
{
	return state;
}

bool Ghost::handleEvent(SDL_Event & e) {
	return false;
}