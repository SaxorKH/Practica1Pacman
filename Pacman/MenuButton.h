#pragma once
#include "GameObject.h"
#include "Texture.h"
class MenuButton :
	public GameObject
{
protected:
	CallBack * callBack;
private:
	SDL_Rect area;
	Texture * texture;

public:
	MenuButton();
	MenuButton(Game*g, SDL_Rect area, CallBack*f);
	~MenuButton();
	void render();
	void update();
	bool handleEvent(SDL_Event & e);
};

