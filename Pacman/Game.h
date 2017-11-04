#pragma once
#include "SDL.h"

class Game
{
private:
	SDL_Window* window = nullptr;

public:
	Game();
	~Game();
};

