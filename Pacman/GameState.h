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

	unsigned int winWidth = 500;
	unsigned int winHeight = 350;
	bool restart = false;
	bool first = true;
	bool end = false;
	// Lee un código numérico del teclado.
	static unsigned int GetCode(Game * g);
	virtual void onEnter();
	virtual void onExit();
public:
	GameState(Game * g);
	GameState(Game*g, TextureType t);
	virtual ~GameState();
	virtual void update();
	virtual void render();
	virtual void handleEvent();
	void setEnd(bool e);
	void setRestart(bool r);
};

