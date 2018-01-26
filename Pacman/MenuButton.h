#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "checkML.h"
class MenuButton :
	public GameObject
{
protected:
	CallBack * callBack;
private:
	SDL_Rect area;
	Texture * texture;
	unsigned int col;

public:
	MenuButton();
	MenuButton(Game*g, SDL_Rect area, unsigned int col, CallBack*f);
	~MenuButton();
	void render();
	void update();
	bool handleEvent(SDL_Event & e);
};

