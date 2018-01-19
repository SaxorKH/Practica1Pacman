#include "PauseState.h"
#include "MenuButton.h"
#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"

PauseState::PauseState(Game* g) : GameState(g, PauseTexture)
{
	SDL_Rect r = SDL_Rect();
	r.w = 124;
	r.h = 51;
	r.y = 278;

	r.x = 48;
	stage->push_back(new MenuButton(g,r,4, resume));
	
	r.x = 188;
	stage->push_back(new MenuButton(g, r, 2, save));

	r.x = 328;
	stage->push_back(new MenuButton(g, r, 3, Restart));
}


PauseState::~PauseState()
{
	
}

void PauseState::resume(Game*g) {
	g->getGameStateMachine()->currentState()->setEnd(true);
}

void PauseState::save(Game * g)
{
	unsigned int code = GetCode(g);

	if (code != 0) {
		g->saveToFile(code);
		resume(g);
	}
}

void PauseState::Restart(Game * g) {
	g->getGameStateMachine()->currentState()->setRestart(true);
}

void PauseState::update() {
	if (restart) {
		Game *g = game;
		g->getGameStateMachine()->popState();
		g->getGameStateMachine()->popState();
		g->getGameStateMachine()->pushState(new PlayState(g));
		g->getGameStateMachine()->pushState(new MainMenuState(g));
	}
	else
		GameState::update();
}

void PauseState::render()
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


void PauseState::onEnter() {
	GameState::onEnter();
	SDL_SetWindowSize(game->getWindow(), winWidth, winHeight);
	SDL_SetWindowPosition(game->getWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}