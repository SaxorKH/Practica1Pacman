#pragma once
#include "SDL.h"
#include "Texture.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"
#define TOTAL_TEXTURAS 5
#define FRAME_RATE 150
#define N_FANTASMAS 4

using namespace std;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	unsigned int winWidth;
	unsigned int winHeight;
	unsigned int cellSize = 25;
	unsigned int startTime = 0;
	bool exit = false;
	bool funcional;
	Texture* textures = nullptr;
	Pacman pacman;
	Ghost fantasmas[N_FANTASMAS];
	GameMap* gameMap;
	string filename = "..\\levels\\level01.dat";

	void getMapDimensions(const string & filename);
	void collision();



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
	const bool nextCell(unsigned int x, unsigned int y, unsigned int dir) const;
	const unsigned int getRows() const;
	const unsigned int getCols() const;
	void getPacmanPos(unsigned int& x, unsigned int& y);
	void endGame();
	void ghostVulnerable();
};

