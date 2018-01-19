#include "PauseState.h"
#include "MenuButton.h"
#include "Game.h"

PauseState::PauseState(Game* g) : GameState(g, PauseTexture)
{
	SDL_Rect r = SDL_Rect();
	stage->push_back(new MenuButton(g, r, resume));
	// todos botones
}


PauseState::~PauseState()
{
	
}

void PauseState::resume(Game*g) {
	g->getGameStateMachine()->popState();
}