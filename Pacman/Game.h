#pragma once
#include "SDL.h"
#include <vector>
#include "GameObject.h"
using namespace std;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	unsigned int winWidth = 800;
	unsigned int winHeight = 600;
	bool exit = false;
	vector<GameObject*> gameObjects;

public:
	Game();
	~Game();

	void run();
	void render();
	void update();
	void handleEvents();
};

