#pragma once
#include "GameCharacter.h"

class Game;

using namespace std;

class Pacman : public GameCharacter
{
private:
	Direction dirbuffer = None; //Movement direction buffer
	unsigned int lives = 3; //Numberof remaining lifes
	unsigned int energy = 0;//Remaining energy
	bool hasEnergy = false;

public:
	Pacman();
	Pacman(Game* g);
	virtual ~Pacman();

	void setPos(unsigned int row, unsigned int col);
	void update();
	void die();
	void bufferUpdate(Direction input);
	void startEnergy();
	void setEnergy(unsigned int en);
	void loadFromfile(istream &archivo, bool saveFile = false);
};

