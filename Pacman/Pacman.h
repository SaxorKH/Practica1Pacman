#pragma once
#include "Texture.h"

class Game;

using namespace std;

class Pacman
{
private:
	unsigned int x = 0;//Position X
	unsigned int y = 0;// Position Y
	unsigned int inix = 0;//Start Position X
	unsigned int iniy = 0;//Start Position Y
	unsigned int dir = 0;//Movement direction
	unsigned int dirbuffer = 0;//Movement direction buffer
	unsigned int lives = 3; //Numberof remaining lifes
	unsigned int energy = 0;//Remaining energy
	unsigned int startTime = 0;
	unsigned int anim = 0;
	Texture* texture = nullptr;
	Game * game = nullptr;
	void forward();
public:
	Pacman();
	Pacman(Game* a, Texture* b);
	~Pacman();
	void setPos(unsigned int row, unsigned int col);
	void render();
	void update();
	void die();
	void bufferUpdate(unsigned int input);
};

