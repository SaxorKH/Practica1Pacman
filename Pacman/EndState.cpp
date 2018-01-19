#include "EndState.h"
#include "Game.h"


EndState::EndState(Game * g) : GameState(g, GameOverTexture)
{
	winTexture = game->getTexture(WinTexture);
}

EndState::~EndState()
{
}
