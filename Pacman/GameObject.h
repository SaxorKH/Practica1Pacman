#pragma once
#include <iostream>
#include<SDL.h>
using namespace std;
class Game;

typedef void CallBack(Game * g);
class GameObject
{
//Se nombran todos los métodos que tendran los diferentes tipos de GameObjects que serán especificados en cadatipo posteriormente
protected:
	Game * game = nullptr;
	GameObject();
	//Se crea el puntero del GameObject al Game
	GameObject(Game * game);

public:
	virtual ~GameObject();

	virtual void render() = 0;
	virtual void update() = 0;
	virtual bool handleEvent(SDL_Event&e) = 0;

};

