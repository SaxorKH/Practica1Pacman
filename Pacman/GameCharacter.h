#pragma once
#include "GameObject.h"
#include "Texture.h"

enum Direction {
	Right,
	Down,
	Left,
	Up
};

class GameCharacter : public GameObject
{
protected:
	unsigned int x = 0;		//Position X
	unsigned int y = 0;		// Position Y
	unsigned int inix = 0;	//Start Position X
	unsigned int iniy = 0;	//Start Position Y
	Direction dir = Right;	//Movement direction
	unsigned int anim = 0;
	unsigned int spriteCol;

	Texture* texture = nullptr;

	GameCharacter();
	GameCharacter(Game * g);
	GameCharacter(Game * g, Texture * t, unsigned int col);

public:
	virtual ~GameCharacter();
	virtual void render();
	virtual void loadFromFile(istream &archivo);
	virtual void saveToFile();
	virtual void setTexture(Texture *t);
	virtual void die();
	int getX();
	int getY();
	void forward();
};

