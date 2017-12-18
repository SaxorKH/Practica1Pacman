#pragma once
#include "Ghost.h"

class SmartGhost :	public Ghost
{
private:
	static const unsigned int ADULT_AGE = 10;
	static const unsigned int OLD_AGE = 1000;
	unsigned int age = 0;

public:
	SmartGhost();
	SmartGhost(Game* a, Texture* b); 
	SmartGhost(Game * g, Texture * t, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir);
	~SmartGhost();

	void update();
	void loadFromFile(istream &archivo);
	void saveToFile(ostream &archivo);
};

