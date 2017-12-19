#pragma once
#include "SDL.h"
#include <list>
#include "texture.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"

#define TOTAL_TEXTURAS 5
#define FRAME_RATE 150
#define TOTAL_LEVELS 2
#define VUL_TIME 10000
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
	unsigned int nChar;
	unsigned int rows;
	unsigned int cols;
	unsigned int points = 0;
	unsigned int currentLevel;

	bool exit = false;
	bool funcional;
	bool saveState = false;
	bool newLevel = true;
	Texture* textures = nullptr;
	list<GameCharacter*> characters;
	GameMap* gameMap = nullptr;
	string levelPrefix = "..\\levels\\level";

	void getMapDimensions(istream & archivo);
	void collision(list<GameCharacter*>::iterator ini);
	void SaveState();
	void cleanMap();
	void renderInterface();
	void renderLetter(char l, unsigned int x, unsigned int y);



public:
	Game();
	~Game();
	const bool getFuncional() const;
	SDL_Renderer * getRenderer() const;
	const unsigned int getCellSize() const;
	void run();
	void render();
	void update();
	bool loadMap(const string& filename, bool savefile = false);
	void handleEvents();
	const bool nextCell(unsigned int x, unsigned int y, Direction dir) const;
	const unsigned int getRows() const;
	const unsigned int getCols() const;
	void getPacmanPos(unsigned int& x, unsigned int& y);
	void endGame();
	void ghostScared(unsigned int energy = 0);
	void nextLevel();
	void increasePoints(unsigned int p);
};

