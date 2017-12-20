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
		unsigned int frameTime = SDL_GetTicks() - startVulTime;
		if (frameTime >= VUL_TIME) {
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

void Pacman::render()
{
	GameCharacter::render();
	SDL_Rect destRect;
	destRect.w = destRect.h = game->getCellSize();
	destRect.y = game->getCellSize()*(4);
	for (unsigned int i = 1; i <= lives; i++) {
		destRect.x = game->getCellSize()*(game->getCols() + i);
		texture->renderFrame(game->getRenderer(), destRect, (unsigned int)Right, spriteCol*2 + 1);
	}
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
