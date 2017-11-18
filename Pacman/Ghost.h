#pragma once
#include "Texture.h"
#include <random>

class Game;

class Ghost
{
private:
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution;
	unsigned int color;
	unsigned int x = 0;//Position X
	unsigned int y = 0;// Position Y
	unsigned int inix = 0;//Start Position X
	unsigned int iniy = 0;//Start Position Y
	unsigned int dir = 0;//Movement direction
	unsigned int anim = 0;
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
};

