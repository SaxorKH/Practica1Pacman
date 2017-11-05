#include "Game.h"
#include <iostream>
using namespace std;


Game::Game()
{
}


Game::~Game()
{
}

void Game::run()
{
	int winX, winY;	//	Posición	de	la	ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First	test	with	SDL", winX, winY,
		winWidth, winHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error	initializing	SDL\n";
	else {	//	Programa	que	usa	SDL
		while (!exit) {
			handleEvents();
			update();
			render();
		}
	}
}

void Game::render()
{
	gameMap.render();
	pacman.render();
}

void Game::update()
{
	gameMap.update();
	pacman.update();
}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			break;
		default:
			break;
		}

		if (event.type == SDL_QUIT)
			exit = true;
	}
}
