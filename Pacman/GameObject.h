#pragma once
#include <iostream>
using namespace std;
class Game;

class GameObject
{
protected:
	Game * game = nullptr;

	GameObject();
	GameObject(Game * game);

public:
	virtual ~GameObject();

	virtual void render();
	virtual void update();
	virtual void loadFromFile(istream &archivo, bool x = false);
	virtual void saveToFile();

};

