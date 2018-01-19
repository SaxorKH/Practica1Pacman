#include "MenuButton.h"
#include "GameState.h"
#include "Game.h"
MenuButton::MenuButton()
{
}

MenuButton::MenuButton(Game * g, SDL_Rect area, unsigned int col, CallBack*f) : GameObject(g)
{

	this->area = area;
	this->col = col;
	texture = game->getTexture(ButtonTexture);
	callBack = f;
}


MenuButton::~MenuButton()
{
}

void MenuButton::render()
{
	texture->renderFrame(game->getRenderer(), area, 0, col);
}

void MenuButton::update()
{
}

bool MenuButton::handleEvent(SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p;
		p.x = event.button.x;
		p.y = event.button.y;
		if(SDL_PointInRect(&p, &area)) {
			(*callBack)(game);
			return true;
		}
	}
	return false;
}
