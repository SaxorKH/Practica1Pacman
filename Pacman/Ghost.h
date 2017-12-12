#pragma once
#include <random>
#include "GameCharacter.h"
class Game;

enum GhostState {
	Alive,
	Escared,
	Dead
};

class Ghost : public GameCharacter
{
private:
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution;
	static const unsigned int vulTime = 10000;
	static const unsigned int deadTime = 5000;

	unsigned int state = 0;
	unsigned int startVulTime = 0;
	unsigned int startDeadTime = 0;
	void forward();
public:
	Ghost();
	Ghost(unsigned int color, Game* a, Texture* b);
	virtual ~Ghost();

	void setPos(unsigned int row, unsigned int col);
	void render();
	void update();
	void vulnerable();
	void die();
	unsigned int getState();
};

