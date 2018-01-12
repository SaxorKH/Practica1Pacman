#pragma once
#include "GameObject.h"

class MenuButton :
	public GameObject
{
private:
	typedef void CallBack(Game * game);
	CallBack * callBack;

public:
	MenuButton();
	MenuButton(Game*g, SDL_Rect area, CallBack * f);
	~MenuButton();
	bool handleEvent(SDL_Event & e);
};

