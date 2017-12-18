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
