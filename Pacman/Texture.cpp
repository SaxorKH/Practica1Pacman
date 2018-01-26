#include "Texture.h"
#include "SDL_image.h"
#include "SDLError.h"
#include "checkML.h"


Texture::Texture()
{
}

Texture::~Texture()
{
	if(texture != nullptr)
		SDL_DestroyTexture(texture);
}
void Texture::load(SDL_Renderer * renderer, string filename, unsigned int numRows, unsigned int numCols)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface == NULL)
		throw(SDLError(IMG_GetError()));
	w = surface->w;
	h = surface->h;
	fw = w / numCols;
	fh = h / numRows;

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
		throw(SDLError(IMG_GetError()));
	SDL_FreeSurface(surface);
}
void Texture::render(SDL_Renderer * renderer, const SDL_Rect & destRect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, 0, NULL, flip);
}
void Texture::renderFrame(SDL_Renderer * renderer, const SDL_Rect & destRect, int row, int col, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;

	if (srcRect.x > w)
		srcRect.x = 0;
	if (srcRect.y > h)
		srcRect.y = 0;

	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
}
