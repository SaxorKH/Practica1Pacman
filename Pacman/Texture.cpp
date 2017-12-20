#include "Texture.h"
#include "SDL_image.h"



Texture::Texture()
{
}

//Destructor de la clase
Texture::~Texture()
{
	if(texture != nullptr)
		SDL_DestroyTexture(texture);
}
//Carga una textura a partir de un archivo cuyo nombre se introduce
bool Texture::load(SDL_Renderer * renderer, string filename, unsigned int numRows, unsigned int numCols)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface == NULL)
		return false;
	w = surface->w;
	h = surface->h;
	fw = w / numCols;
	fh = h / numRows;

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return true;
}
//Dibuja la textura en el rectangula destino proporcionado
void Texture::render(SDL_Renderer * renderer, const SDL_Rect & destRect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, 0, NULL, flip);
}
//Dibuja un frameindicado de la textura en un rectangulo destino
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
