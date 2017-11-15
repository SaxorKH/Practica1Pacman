#include "Pacman.h"
#include "Game.h"


Pacman::Pacman()
{
}

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
	unsigned int frameTime = SDL_GetTicks() - startTime;
	if(FRAME_RATE < frameTime){
		if (game->nextCell(x, y, dirbuffer)) {
			dir = dirbuffer;
			forward();
		}
		else if (game->nextCell(x, y, dir))
			forward();
		startTime = SDL_GetTicks();
		
	}
}

void Pacman::die()
{
}

void Pacman::forward() {
	if (dir == 0)
		x++;
	else if (dir == 1)
		y++;
	else if (dir == 2)
		x--;
	else if (dir == 3)
		y--;
}
void Pacman::bufferUpdate(unsigned int input) {
	if ((input <= 3) && (input >= 0))
		dirbuffer = input;
}
