#include "GameState.h"
#include "Game.h"





unsigned int GameState::GetCode(Game * g)
{
	SDL_Event event;
	bool state = true;
	unsigned int code = 0;
	while (state) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT) {
			g->setExit(true);
			state = false;
		}
		else if (event.key.keysym.sym == SDLK_RETURN)
			state = false;
		else if (event.key.type == SDL_KEYDOWN && event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
			code = 10 * code + (event.key.keysym.sym - SDLK_0);
	}
	
	return code;
}

GameState::GameState(Game * g)
{
	game = g;
	stage = new list<GameObject*>();
}

GameState::~GameState()
{
	delete stage;
}

void GameState::update()
{
	if (end)
		game->getGameStateMachine()->popState();
	else
		for (list<GameObject*>::iterator it = stage->begin(); it != stage->end(); it++)
			(*it)->update();
}

void GameState::render()
{
	for (list<GameObject*>::iterator it = stage->begin(); it != stage->end(); it++)
		(*it)->render();
}

void GameState::handleEvent()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) 
			game->setExit(true);
		else {
			list<GameObject*>::iterator it = stage->begin();
			while (it != stage->end() && !(*it)->handleEvent(event))
				it++;
		}
	}
}

void GameState::setEnd(bool e)
{
	end = e;
}

void GameState::setRestart(bool r)
{
	restart = r;
	setEnd(true);
}

void GameState::Restart(Game * g)
{
	g->getGameStateMachine()->currentState()->setRestart(true);
}

void GameState::onEnter()
{
	first = false;
	SDL_SetWindowSize(game->getWindow(), winWidth, winHeight);
	SDL_SetWindowPosition(game->getWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void GameState::onExit()
{
	first = true;
}
