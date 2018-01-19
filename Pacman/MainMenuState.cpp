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
	f = start;
	MenuButton * mb = new MenuButton(g, destRect, 0, f);
	stage->push_back(mb);


	destRect.x = 314;
	mb = new MenuButton(g, destRect, 1, loadState);
	stage->push_back(mb);
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::render()
{
	if (first) {
		onEnter();
	}
	SDL_Rect r;
	r.x = r.y = 0;
	r.w = winWidth;
	r.h = winHeight;
	texture->render(game->getRenderer(), r);
	GameState::render();
}


void MainMenuState::loadState(Game * g)
{
	unsigned int code = GetCode(g);
	
	stringstream ss;
	ss << code;
	string filename = levelPrefix + "Save" + ss.str() + ".pac";
	g->setFilename(filename);
}

void MainMenuState::start(Game * g)
{
	((MainMenuState*) g->getGameStateMachine()->currentState())->setEnd(true);
}

void MainMenuState::onEnter() {
	GameState::onEnter();
	SDL_SetWindowSize(game->getWindow(), winWidth, winHeight);
	SDL_SetWindowPosition(game->getWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}