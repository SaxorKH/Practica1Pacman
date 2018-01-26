#pragma once
#include "GameState.h"
#include "checkML.h"
class EndState :
	public GameState
{
private:
	Texture * winTexture = nullptr;
	Texture * loseTexture = nullptr;
	bool win = false;
public:
	EndState(Game * g);
	~EndState();
	void render();
	void setWin(bool w);
	void update();
};

