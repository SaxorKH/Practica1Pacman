#pragma once
#include <iostream>
#include<SDL.h>
using namespace std;
class Game;

class GameObject
{
//Se nombran todos los métodos que tendran los diferentes tipos de GameObjects que serán especificados en cadatipo posteriormente
protected:
	Game * game = nullptr;
	SDL_Rect area;
	GameObject();
	//Se crea el puntero del GameObject al Game
	GameObject(Game * game);

public:
	virtual ~GameObject();

	virtual void render();
	virtual void update();
	virtual bool handleEvent(SDL_Event&e);

};

