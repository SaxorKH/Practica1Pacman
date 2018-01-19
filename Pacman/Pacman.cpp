#include "Pacman.h"
#include "Game.h"

Pacman::Pacman()
{
}

Pacman::Pacman(Game* g) : GameCharacter(g, 5)
{
}


Pacman::~Pacman()
{
}

void Pacman::update() {
	if (hasEnergy) {
		energy++;
		unsigned int frameTime = SDL_GetTicks() - startVulTime;
		if (frameTime >= VUL_TIME) {
			hasEnergy = false;
			energy = 0;
			startVulTime = SDL_GetTicks();
		}
	}
	if (dirbuffer != None && game->nextCell(x, y, dirbuffer)) {
		dir = dirbuffer;
		forward();
	}
	else if (dir != None && game->nextCell(x, y, dir))
		forward();
	GameCharacter::update();
}


void Pacman::die()
{
	if (lives == 0)
		game->endGame();
	else {
		lives--;
		x = inix;
		y = iniy;
		dir = None;
	}
}

void Pacman::loadFromSavefile(istream & archivo)
{
	GameCharacter::loadFromFile(archivo);
	archivo >> energy;
	if (energy != 0) {
		game->ghostScared(energy);
	}
	archivo >> lives;
}

void Pacman::saveToFile(ostream & archivo)
{
	GameCharacter::saveToFile(archivo);
	archivo << energy << " " << lives << endl;
}

bool Pacman::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			dirbuffer = Right;
			return true;
		case SDLK_DOWN:
			dirbuffer = Down;
			return true;
		case SDLK_LEFT:
			dirbuffer = Left;
			return true;
		case SDLK_UP:
			dirbuffer = Up;
			return true;
		default:
			return false;
		}
	}
	return false;
}

void Pacman::startEnergy()
{
	hasEnergy = true;
}

void Pacman::setEnergy(unsigned int en)
{
	energy = en;
	startVulTime = SDL_GetTicks() - en;
	startEnergy();
}

unsigned int Pacman::getLives() {
	return lives;
}
