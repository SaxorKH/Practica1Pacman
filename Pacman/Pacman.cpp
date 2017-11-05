#include "Pacman.h"



Pacman::Pacman(Game* g, Texture* t)
{
	game = g;
	texture = t;
}


Pacman::~Pacman()
{
}

void Pacman::setPos(unsigned int row, unsigned int col) {
	inix = x = col;
	iniy = y = row;
}
void Pacman::Render() {
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	destRect.w = destRect.h = cellSize;
	destRect.x = x * cellSize;
	destRect.y = y * cellSize;
	texture->renderFrame(game->getRenderer,destRect,dir,11);
}

void Pacman::Update() {
	if (game.NextCell(dirbuffer)) {
		dir = dirbuffer;
		Forward();
	}
	else if (game.NextCell(dir))
		Forward();
}

void Pacman::Forward() {
	if (dir == 0)
		x++;
	else if (dir == 1)
		y++;
	else if (dir == 2)
		x--;
	else if (dir == 3)
		y--;
}
void Pacman::BufferUpdate(unsigned int input) {
	if ((input <= 3) && (input >= 0))
		dirbuffer = input;
}
