#pragma once
#include <list>
#include "GameObject.h"
#include "Texture.h"
class Game;
enum TextureType;
using namespace std;


class GameState
{
protected:
	list<GameObject*> * stage;
	Game * game = nullptr;
	Texture * texture = nullptr;
	SDL_Event event;

	bool first = true;
	// Lee un código numérico del teclado.
	unsigned int GetCode();
	virtual void onEnter();
	virtual void onExit();
public:
	GameState(Game * g);
	GameState(Game*g, TextureType t);
	virtual ~GameState();
	virtual void update();
	virtual void render();
	virtual void handleEvent();
};

