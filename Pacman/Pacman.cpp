#include "Pacman.h"
#include "Game.h"

Pacman::Pacman()
{
}

Pacman::Pacman(Game* g) : GameCharacter(g, nullptr, 6)
{
}


Pacman::~Pacman()
{
}

void Pacman::setPos(unsigned int row, unsigned int col) {
	inix = x = col;
	iniy = y = row;
}
void Pacman::render() {
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	destRect.w = destRect.h = cellSize;
	destRect.x = x * cellSize;
	destRect.y = y * cellSize;
	anim = int(((SDL_GetTicks() / FRAME_RATE) % 2));
	texture->renderFrame(game->getRenderer(), destRect, dir, 10 + anim);
}

void Pacman::update() {
		if (game->nextCell(x, y, dirbuffer)) {
			dir = dirbuffer;
			forward();
		}
		else if (game->nextCell(x, y, dir))
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
	}
}

void Pacman::bufferUpdate(Direction input) {
	if ((input <= 3) && (input >= 0))
		dirbuffer = input;
}
