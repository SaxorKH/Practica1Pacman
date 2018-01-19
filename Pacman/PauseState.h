#pragma once
#include "GameState.h"
class PauseState :
	public GameState
{
public:
	PauseState(Game* game);
	~PauseState();
	static void resume(Game*g);
};

