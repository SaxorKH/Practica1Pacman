#pragma once
#include "SDL.h"
#include "Texture.h"
#include "Pacman.h"
#include "GameMap.h"
#define TOTAL_TEXTURAS 2

using namespace std;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	unsigned int winWidth;
	unsigned int winHeight;
	unsigned int cellSize = 128;
	bool exit = false;
	bool funcional;
	Texture textures[TOTAL_TEXTURAS];
	Pacman pacman;
	GameMap gameMap;



public:
	Game();
	~Game();

	const bool getFuncional() const;
	SDL_Renderer * getRenderer() const;
	const unsigned int getCellSize() const;
	void run();
	void render();
	void update();
	bool loadMap(const string& filename);
	void handleEvents();
};

