#pragma once
#include "GameCharacter.h"
class Game;

enum GhostState {
	Alive,
	Scared,
	Dead,
	Adult,
	Old
};

class Ghost : public GameCharacter
{
protected:
	static const unsigned int deadTime = 5000;
	GhostState defaultState = Alive;

	unsigned int state = 0;
	unsigned int startDeadTime = 0;

	bool sinSalida(Direction dirAux);

public:
	Ghost();
	Ghost(unsigned int color, Game* a, Texture* b);
	Ghost(Game * g, Texture * t, unsigned int col, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir);
	virtual ~Ghost();

	void setPos(unsigned int row, unsigned int col);
	virtual void render();
	virtual void update();
	virtual void saveToFile(ostream & archivo);
	void scared(unsigned int energy = 0);
	virtual void die();
	unsigned int getState();
};

