#include "SDL.h"
#include "Texture.h"
#include <iostream>
#include <vector>
#define TIME_PER_FRAME 100

using namespace std;


int main(int argc, char* argv[]) {
	//	Variables
	SDL_Window*	window = nullptr;
	SDL_Renderer*	renderer = nullptr;
	

	SDL_Rect desRect;

	const int winWidth = 800;
	const int winHeight = 600;

	unsigned int velocidad = 20;




	//	Inicialización	del	sistema,	ventana	y	renderer
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error	initializing	SDL\n";
	else {	//	Programa	que	usa	SDL

		vector<Texture> textures(3);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);	//	RGB	y	alpha

		string filename = "..\\images\\background1.png";	//	Nombre	del	fichero	con	la	imagen
		textures[0].load(renderer, filename);

		filename = "..\\images\\dog.png";
		textures[1].load(renderer, filename, 1, 6);
		unsigned int dogFrames = 6;
		unsigned int actualDogFrame = 0;

		filename = "..\\images\\helicopter.png";
		textures[2].load(renderer, filename, 1, 5);
		unsigned int helFrames = 5;
		unsigned int actualHelFrame = 0;


		unsigned int textFrameW = 768 / 6;
		unsigned int textFrameH = 82 / 1;

		unsigned int textFrameWHel = 640 / 5;
		unsigned int textFrameHHel = 55 / 1;

		unsigned int dist = winWidth + 100 * 2;


		while (!exit) {
			//	Actualizar posiciones	de	objetos	del	juego
			SDL_RenderClear(renderer);	//	Borra	la	pantalla

			desRect.x = desRect.y = 0;
			desRect.h = winHeight;
			desRect.w = winWidth;

			textures[0].render(renderer, desRect);


			desRect.h = desRect.w = 100;


			desRect.y = 500;

			actualDogFrame = int((SDL_GetTicks() / TIME_PER_FRAME) % dogFrames);
			desRect.x = int(((SDL_GetTicks() * velocidad) / TIME_PER_FRAME) % dist) - desRect.w;
			textures[1].renderFrame(renderer, desRect, 0, actualDogFrame);

			desRect.y = 0;

			actualHelFrame = int((SDL_GetTicks() / TIME_PER_FRAME) % helFrames);
			desRect.x = dist - (int(((SDL_GetTicks() * velocidad) / TIME_PER_FRAME) % dist)) - desRect.w;
			textures[2].renderFrame(renderer, desRect, 0, actualHelFrame);



			SDL_RenderPresent(renderer);	//	Muestra	la	escena


			
		}


		
	}
	SDL_Quit();

	return 0;
}