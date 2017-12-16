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

		distX = pacX - x;
		distY = pacY - y;
		
		break;
	}

	age++;
	if (age == ADULT_AGE)
		state = Adult;
	if (age == OLD_AGE)
		state = Old;
}

void SmartGhost::loadFromFile(istream & archivo)
{
	Ghost::loadFromFile(archivo);
	archivo >> age;
	if (age >= OLD_AGE)
		state = Old;
	else if (age >= ADULT_AGE) {
		state = Adult;
		defaultState = Adult;
	}
}

void SmartGhost::saveToFile(ostream & archivo)
{
}

SmartGhost::SmartGhost()
{
}

SmartGhost::SmartGhost(Game * a, Texture * b) : Ghost(4,  a, b)
{
}


SmartGhost::~SmartGhost()
{
}
