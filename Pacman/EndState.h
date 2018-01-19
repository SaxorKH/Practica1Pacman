#pragma once
#include "GameState.h"
class EndState :
	public GameState
{
private:
	Texture * winTexture = nullptr;
public:
	EndState(Game * g);
	~EndState();
};

