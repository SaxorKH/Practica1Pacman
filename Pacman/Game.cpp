#include "Game.h"
#include <iostream>
#include <fstream>
using namespace std;




Game::Game()
{
	int winX, winY;	//	Posición	de	la	ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	getMapDimensions(filename);

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First	test	with	SDL", winX, winY,
		winWidth, winHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		cout << "Error	initializing	SDL\n";
		funcional = false;
	}
	else {
		textures = new Texture[TOTAL_TEXTURAS];
		funcional = textures[0].load(renderer, "..\\images\\characters1.png", 4, 14);
		funcional = textures[1].load(renderer, "..\\images\\wall2.png");
		funcional = textures[2].load(renderer, "..\\images\\food2.png");
		funcional = textures[3].load(renderer, "..\\images\\food3.png");
		funcional = textures[4].load(renderer, "..\\images\\burguer1.png");
		if (!funcional)
			cout << "Error loading textures\n";
		else {
			pacman = Pacman(this, &textures[0]);
			for (unsigned int i = 0; i < N_FANTASMAS; i++)
				fantasmas[i] = Ghost(i, this, &textures[0]);


			if (!loadMap(filename)) {
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
	delete[] textures;
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
	unsigned int initTime = SDL_GetTicks();
	SDL_RenderClear(renderer);
	gameMap->render();
	pacman.render();
	for (unsigned int i = 0; i < N_FANTASMAS; i++)
		fantasmas[i].render();
	SDL_RenderPresent(renderer);	//	Muestra	la	escena
}

void Game::update()
{
	unsigned int frameTime = SDL_GetTicks() - startTime;
	if (FRAME_RATE < frameTime) {
		gameMap->update();
		pacman.update();
		for (unsigned int i = 0; i < N_FANTASMAS; i++)
			fantasmas[i].update();
		startTime = SDL_GetTicks();
	}
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
	gameMap = new GameMap(rows, cols, &textures[1], &textures[2], &textures[3], this);

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
				gameMap->setCellType(i, j, Empty);
				fantasmas[0].setPos(i, j);
				break;
			case 6:
				gameMap->setCellType(i, j, Empty);
				fantasmas[1].setPos(i, j);
				break;
			case 7:
				gameMap->setCellType(i, j, Empty);
				fantasmas[2].setPos(i, j);
				break;
			case 8:
				gameMap->setCellType(i, j, Empty);
				fantasmas[3].setPos(i, j);
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
		x = (x + 1) % getCols();
		break;
	case 1:
		y = (y + 1) % getRows();
		break;
	case 2:
		if (x == 0)
			x = getCols();
		x--;
		break;
	case 3:
		if (y == 0)
			y = getRows();
		y--;
		break;
	}

	return gameMap->getCellType(y, x) != Wall;
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

const unsigned int Game::getRows() const
{
	return gameMap->getRows();
}

const unsigned int Game::getCols() const
{
	return gameMap->getCols();
}
void Game::getPacmanPos(unsigned int& x, unsigned int& y) {
	x = pacman.getX();
	y = pacman.getY();
}

void Game::endGame()
{
	exit = true;
}
