#pragma once
#include "GameState.h"
class MainMenuState :
	public GameState
{
private:
	const unsigned int winWidth = 500;
	const unsigned int winHeight = 350;

	bool inicio = true;
public:
	MainMenuState(Game * g);
	~MainMenuState();

	// Le pide un c�digo num�rico al jugador y carga la partida.
	void LoadState();
	static void update(Game * g);
};

