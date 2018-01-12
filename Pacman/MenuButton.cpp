#include "MenuButton.h"

MenuButton::MenuButton()
{
}

MenuButton::MenuButton(Game * g, SDL_Rect area, CallBack * f) : GameObject(g)
{
	this->area = area;
	callBack = f;
}


MenuButton::~MenuButton()
{
}

bool MenuButton::handleEvent(SDL_Event & event)
{
	int x;
	int y;
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		x = event.button.x;
		y = event.button.y;
		if (x >= area.x && x <= (area.x + area.w) && y >= area.y && y <= (area.y + area.h)) {
			(*callBack)(game);
			return true;
		}
	}
	return false;
}
