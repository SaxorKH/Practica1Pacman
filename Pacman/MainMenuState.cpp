#include "MainMenuState.h"
#include "Game.h"
#include "MenuButton.h"
#include <sstream>


MainMenuState::MainMenuState(Game * g) : GameState(g, MainTexture)
{
	SDL_Rect destRect;
	destRect.x = 64;
	destRect.y = 278;
	destRect.w = 124;
	destRect.h = 51;
	CallBack * f;
	f = update;
	MenuButton mb = MenuButton(g, destRect, f);
}


MainMenuState::~MainMenuState()
{
}


void MainMenuState::LoadState()
{
	unsigned int code = GetCode();
	
	stringstream ss;
	ss << code;
	string filename = levelPrefix + "Save" + ss.str() + ".pac";
	game->setFilename(filename);
}

void MainMenuState::update(Game * g)
{
}