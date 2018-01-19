#pragma once
#include "GameState.h"
class PauseState :
	public GameState
{
public:
	PauseState(Game* game);
	~PauseState();
	static void resume(Game*g);
	// Le pide un código numérico al jugador y guada la partida.
	static void save(Game *g);
	static void Restart(Game * g);
	void update();
	void render();
	void onEnter();
};

