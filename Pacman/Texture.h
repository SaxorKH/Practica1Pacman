#pragma once
#include "SDL.h"
#include <string>
using namespace std;

class Texture
{
private:
	SDL_Texture* texture = nullptr;
	unsigned int w = 0; // Texture width (pixels)
	unsigned int h = 0; // Texture height (pixels)
	unsigned int fw = 0; // Frame width (pixels)
	unsigned int fh = 0; // Frame height (pixels)

public:
	Texture();
	~Texture();
	bool load(SDL_Renderer* renderer, string filename, unsigned int numRows = 1, unsigned int numCols = 1);
	void render(SDL_Renderer* renderer, const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

