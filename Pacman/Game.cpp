#include "Game.h"
#include <iostream>
#include <fstream>
using namespace std;




Game::Game()
{
	int winX, winY;	//	Posición	de	la	ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	getMapDimensions("..\\levels\\nivelPrueba.txt");

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
		else {
			pacman = Pacman(this, &textures[0]);

			if (!loadMap("..\\levels\\nivelPrueba.txt")) {
				cout << "Error cargando mapa";
				funcional = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			}
		}
	}
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
	gameMap->render();
	pacman.render();
	SDL_RenderPresent(renderer);	//	Muestra	la	escena
}

void Game::update()
{
	gameMap->update();
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
	gameMap = new GameMap(rows, cols, &textures[1], this);

	winWidth = cols*cellSize;
	winHeight = rows*cellSize;

	for(unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++) {
			archivo >> cellVal;
			switch (cellVal) {
			case 0:
				gameMap->setCellType(i, j, Empty);
				break;
			case 1:
				gameMap->setCellType(i, j, Wall);
				break;
			case 2:
				gameMap->setCellType(i, j, Food);
				break;
			case 3:
				gameMap->setCellType(i, j, Vitamins);
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
				gameMap->setCellType(i, j, Empty);
				pacman.setPos(i, j);
				break;
			}
		}
	return true;
}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYDOWN:
			unsigned int dir;
			switch(event.key.keysym.sym) {
			case SDLK_RIGHT:
				dir = 0;
				break;
			case SDLK_DOWN:
				dir = 1;
				break;
			case SDLK_LEFT:
				dir = 2;
				break;
			case SDLK_UP:
				dir = 3;
				break;
			}
			pacman.bufferUpdate(dir);
		default:
			break;
		}
	}
}

const bool Game::nextCell(unsigned int x, unsigned int y, unsigned int dir) const
{
	switch (dir) {
	case 0:
		x++;
		break;
	case 1:
		y++;
		break;
	case 2:
		x--;
		break;
	case 3:
		y--;
		break;
	}

	return gameMap->getCellType(x, y) != Wall;
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

void Game::getMapDimensions(const string & filename) {
	ifstream archivo;

	archivo.open(filename);

	unsigned int rows, cols;
	archivo >> rows;
	archivo >> cols;

	winWidth = cols*cellSize;
	winHeight = rows*cellSize;
}
