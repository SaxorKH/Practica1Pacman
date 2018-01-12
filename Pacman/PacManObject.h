#pragma once
#include "GameObject.h"
class PacManObject :
	public GameObject
{
public:
	PacManObject();
	PacManObject(Game * game);
	virtual ~PacManObject();
	virtual void loadFromFile(istream &archivo);
	virtual void saveToFile(ostream &archivo);
};

