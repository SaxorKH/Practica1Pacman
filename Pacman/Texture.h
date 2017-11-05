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
	
	// Carga un archivo de imagen como textura. Añadiendo filas y columnas puede funcionar como tileset.
	bool load(SDL_Renderer* renderer, string filename, unsigned int numRows = 1, unsigned int numCols = 1); 

	// Dibuja la textura completa en el rectángulo destino dado. 
	void render(SDL_Renderer* renderer, const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	// Dibuja una celda específica de la textura según la fila y columna dada, en el rectángulo destino dado.
	void renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE); 
};

