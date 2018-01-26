#pragma once
#include "GameState.h"
#include "checkML.h"
class MainMenuState :
	public GameState
{
private:
	bool inicio = true;
	Texture * texture = nullptr;
public:
	MainMenuState(Game * g);
	~MainMenuState();

	void render();

	// Le pide un código numérico al jugador y carga la partida.
	static void load(Game * g);
	static void start(Game * g);
};

