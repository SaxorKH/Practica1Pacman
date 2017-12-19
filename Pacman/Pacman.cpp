#include "Pacman.h"
#include "Game.h"

Pacman::Pacman()
{
}

Pacman::Pacman(Game* g) : GameCharacter(g, nullptr, 5)
{
}


Pacman::~Pacman()
{
}

void Pacman::setPos(unsigned int row, unsigned int col) {
	inix = x = col;
	iniy = y = row;
}

void Pacman::update() {
	if (hasEnergy) {
		energy++;
		if (energy == VUL_TIME) {
			hasEnergy = false;
			energy = 0;
		}
	}
		if (dirbuffer != None && game->nextCell(x, y, dirbuffer)) {
			dir = dirbuffer;
			forward();
		}
		else if (dir != None && game->nextCell(x, y, dir))
			forward();
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

void Pacman::bufferUpdate(Direction input) {
		dirbuffer = input;
}

void Pacman::loadFromfile(istream & archivo, bool saveFile)
{
	GameCharacter::loadFromFile(archivo);
	if (saveFile) {
		unsigned int energy;
		archivo >> energy;
		if (energy != 0) {
			game->ghostScared(energy);
		}
		archivo >> lives;
	}
}

void Pacman::startEnergy()
{
	hasEnergy = true;
}

void Pacman::setEnergy(unsigned int en)
{
	energy = en;
	startEnergy();
}
