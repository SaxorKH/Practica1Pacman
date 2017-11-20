#pragma once
#include "Texture.h"
#include <random>

class Game;

class Ghost
{
private:
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution;
	static const unsigned int vulTime = 10000;
	static const unsigned int deadTime = 5000;

	unsigned int color;
	unsigned int x = 0;//Position X
	unsigned int y = 0;// Position Y
	unsigned int inix = 0;//Start Position X
	unsigned int iniy = 0;//Start Position Y
	unsigned int dir = 0;//Movement direction
	unsigned int anim = 0;
	unsigned int state = 0;
	unsigned int startVulTime = 0;
	unsigned int startDeadTime = 0;
	Texture* texture = nullptr;
	Game * game = nullptr;
	void forward();
public:
	Ghost();
	Ghost(unsigned int color, Game* a, Texture* b);
	~Ghost();
	void setPos(unsigned int row, unsigned int col);
	void render();
	void update();
	void vulnerable();
	void die();
	unsigned int getState();

	int getX();
	int getY();
};

