#include "EndState.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "MainMenuState.h"


EndState::EndState(Game * g) : GameState(g)
{
	winTexture = game->getTexture(WinTexture);
	loseTexture = game->getTexture(GameOverTexture);

	SDL_Rect r = SDL_Rect();
	r.w = 124;
	r.h = 51;
	r.y = 278;
	r.x = 188;
	stage->push_back(new MenuButton(g, r, 3, Restart));
}

EndState::~EndState()
{
}

void EndState::render()
{
	if (first) {
		onEnter();
	}
	SDL_Rect r;
	r.x = r.y = 0;
	r.w = winWidth;
	r.h = winHeight;
	if (win)
		winTexture->render(game->getRenderer(), r);
	else
		loseTexture->render(game->getRenderer(), r);
	GameState::render();
}

void EndState::setWin(bool w)
{
	win = w;
}

void EndState::update()
{
	if (restart) {
		Game *g = game;
		g->getGameStateMachine()->pushState(new PlayState(g));
		g->getGameStateMachine()->pushState(new MainMenuState(g));
	}
	else
		GameState::update();
}

