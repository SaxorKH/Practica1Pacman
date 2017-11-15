#pragma once
#include "SDL.h"
#include "Texture.h"
#include "Pacman.h"
#include "GameMap.h"
#define TOTAL_TEXTURAS 5
#define FRAME_RATE 200

using namespace std;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	unsigned int winWidth;
	unsigned int winHeight;
	unsigned int cellSize = 32;
	bool exit = false;
	bool funcional;
	Texture* textures = nullptr;
	Pacman pacman;
	GameMap* gameMap;

	void getMapDimensions(const string & filename);



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
};

