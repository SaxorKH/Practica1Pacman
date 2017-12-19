#include "SmartGhost.h"
#include "Game.h"


void SmartGhost::update()
{
	

	switch (state) {
	default:
		Ghost::update();
		break;
	case Old:
		break;
	case Adult:
		unsigned int pacXAux, pacYAux;
		game->getPacmanPos(pacXAux, pacYAux);
		int pacX, pacY;
		pacX = pacXAux;
		pacY = pacYAux;
		int distX, distY;

		Direction mejorDir;
		int mejor =  999;
		if (sinSalida(dir))
			dir = (Direction) ((dir + 2) % 2);
		for (int i = 0; i < 4; i++) {
			if (i != ((dir+2)%4) && game->nextCell(x, y, (Direction)i)) {
				switch ((Direction)i) {
				default:
					break;
				case Up:
					distX = pacX - x;
					distY = pacY - y + 1;
					break;
				case Left:
					distX = pacX - x + 1;
					distY = pacY - y;
					break;
				case Down:
					distX = pacX - x;
					distY = pacY - y - 1;
					break;
				case Right:
					distX = pacX - x - 1;
					distY = pacY - y;
					break;
				}
				if (abs(distX) + abs(distY) < mejor) {
					mejorDir = (Direction)i;
					mejor = abs(distX) + abs(distY);
				}
			}
		}
			dir = mejorDir;

		forward();
		break;
	}

	age++;
	if (age == ADULT_AGE) {
		if(state != Scared)
			state = Adult;
		defaultState = Adult;
	}
	if (age == OLD_AGE) {
		state = Old;
		defaultState = Old;
	}
		
}

void SmartGhost::loadFromFile(istream & archivo, bool savefile)
{
	Ghost::loadFromFile(archivo);
	archivo >> age;
	if (age >= OLD_AGE){
		state = Old;
		defaultState = Old;
	}
	else if (age >= ADULT_AGE) {
		state = Adult;
		defaultState = Adult;
	}
}

void SmartGhost::saveToFile(ostream & archivo)
{
}

void SmartGhost::die()
{
	if (state != Old) {
		Ghost::die();
	}
	game->increasePoints(200);
}



SDL_Rect SmartGhost::calcDestRect()
{
	if (age >= ADULT_AGE)
		return GameCharacter::calcDestRect();
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	unsigned int ghostSize = cellSize / (3.0f - (age * 2.0f / ADULT_AGE));
	destRect.w = destRect.h = ghostSize;
	destRect.x = x * cellSize + cellSize / 2 - ghostSize / 2;
	destRect.y = y * cellSize + cellSize / 2 - ghostSize / 2;
	return destRect;
}

SmartGhost::SmartGhost()
{
}

SmartGhost::SmartGhost(Game * a, Texture * b) : Ghost(4,  a, b)
{
}

SmartGhost::SmartGhost(Game * g, Texture * t, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir) : Ghost(g, t, 4, inix, iniy, x, y, dir)
{
	forward();
}


SmartGhost::~SmartGhost()
{
}
