#include "Game.h"
#include <iostream>
#include <fstream>
using namespace std;


Game::Game()
{
	int winX, winY;	//	Posición	de	la	ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	loadMap("");

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First	test	with	SDL", winX, winY,
		winWidth, winHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		cout << "Error	initializing	SDL\n";
		funcional = false;
	}
	else {
		funcional = textures[0].load(renderer, "..\\images\\characters1.png", 4, 14);
		funcional = textures[1].load(renderer, "..\\images\\wall2.png");
		if (!funcional)
			cout << "Error loading textures\n";
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
}


Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::run()
{
	while (!exit) {
			handleEvents();
			update();
			render();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	gameMap.render();
	pacman.render();
}

void Game::update()
{
	gameMap.update();
	pacman.update();
}

bool Game::loadMap(const string & filename)
{
	ifstream archivo;

	archivo.open(filename);
	if (!archivo.is_open())
		return false;

	unsigned int rows, cols;
	archivo >> rows;
	archivo >> cols;
	unsigned int cellVal;
	gameMap = GameMap(rows, cols, &textures[1]);

	winWidth = cols*cellSize;
	winHeight = rows*cellSize;

	for(unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++) {
			archivo >> cellVal;
			switch (cellVal) {
			case 0:
				gameMap.setCellType(i, j, GameMap.MapCell.Empty);
				break;
			case 1:
				gameMap.setCellType(i, j, sfsf);
				break;
			case 2:
				gameMap.setCellType(i, j, sfsf);
				break;
			case 3:
				gameMap.setCellType(i, j, sfsf);
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				pacman.setPos(i, j);
				break;
			}
		}
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

const bool Game::getFuncional() const
{
	return funcional;
}

SDL_Renderer * Game::getRenderer() const
{
	return renderer;
}

const unsigned int Game::getCellSize() const
{
	return cellSize;
}
