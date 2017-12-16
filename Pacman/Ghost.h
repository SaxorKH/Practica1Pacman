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
	static const unsigned int vulTime = 10000;
	static const unsigned int deadTime = 5000;
	GhostState defaultState = Alive;

	unsigned int state = 0;
	unsigned int startVulTime = 0;
	unsigned int startDeadTime = 0;

	bool sinSalida(Direction dirAux);

public:
	Ghost();
	Ghost(unsigned int color, Game* a, Texture* b);
	virtual ~Ghost();

	void setPos(unsigned int row, unsigned int col);
	void render();
	virtual void update();
	void vulnerable();
	void die();
	unsigned int getState();
};

