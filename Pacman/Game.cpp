#include "Game.h"
#include "SmartGhost.h"
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "PlayState.h"
#include "MainMenuState.h"
#include "EndState.h"
#include "SDLError.h"
#include "checkML.h"
using namespace std;




Game::Game()
{
	unsigned int winWidth = 500;
	unsigned int winHeight = 350;
	int winX, winY;	//	Posición	de	la	ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	try {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("Pacman", winX, winY,
			winWidth, winHeight, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == nullptr || renderer == nullptr) {
			throw SDLError(SDL_GetError());
		}
		int i = 0;
		try {
			textures = new Texture[TOTAL_TEXTURAS];
			textures[0].load(renderer, "..\\images\\characters1.png", 4, 14);
			i++;
			textures[1].load(renderer, "..\\images\\wall2.png");
			i++;
			textures[2].load(renderer, "..\\images\\food2.png");
			i++;
			textures[3].load(renderer, "..\\images\\food3.png");
			i++;
			textures[4].load(renderer, "..\\images\\font.jpg", 10, 10);
			i++;
			textures[5].load(renderer, "..\\images\\MenuInicio.png");
			i++;
			textures[6].load(renderer, "..\\images\\MenuPausa.png");
			i++;
			textures[7].load(renderer, "..\\images\\GameOver.png");
			i++;
			textures[8].load(renderer, "..\\images\\Victoria.png");
			i++;
			textures[9].load(renderer, "..\\images\\Botones.png", 1, 5);
			i++;


			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			gameStateMachine = new GameStateMachine();
			gameStateMachine->pushState(new EndState(this));
			gameStateMachine->pushState(new PlayState(this));
			gameStateMachine->pushState(new MainMenuState(this));
		}
		catch (SDLError e) {
			cout << "Error al cargar textura " << i << ":" << endl;
			throw e;
		}
	}
	catch (SDLError& error) {
		cout << error.what() << endl;
	}
}

Game::~Game()
{
	delete gameStateMachine;
	if (textures != nullptr) {
		for (int i = 0; i < TOTAL_TEXTURAS; i++)
			textures[i].~Texture();
		delete[] textures;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	while (!exit) {
		handleEvents();
		if (gameStateMachine->currentState() == nullptr)
			exit = true;
		else
			update();
		if (load) {
			load = false;
			((PlayState*)gameStateMachine->currentState())->loadSaveFile(filename);
		}
		if (win) {
			((EndState*)gameStateMachine->currentState())->setWin(true);
		}
		if (gameStateMachine->currentState() == nullptr)
			exit = true;
		else
			render();
		if (save) {
			((PlayState*)gameStateMachine->currentState())->saveToFile(saveCode);
			save = false;
		}
	}
}

const bool Game::nextCell(unsigned int x, unsigned int y, Direction dir) const
{
	return ((PlayState*)gameStateMachine->currentState())->nextCell(x, y, dir);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	gameStateMachine->currentState()->render();
	SDL_RenderPresent(renderer);	//	Muestra	la	escena
}

void Game::update()
{
	gameStateMachine->currentState()->update();
}

void Game::handleEvents()
{
	gameStateMachine->currentState()->handleEvent();
}

SDL_Renderer * Game::getRenderer() const
{
	return renderer;
}

SDL_Window * Game::getWindow() const
{
	return window;
}

const unsigned int Game::getCellSize() const
{
	return ((PlayState*)gameStateMachine->currentState())->getCellSize();
}


void Game::collision(GameCharacter&c)
{
	((PlayState*)gameStateMachine->currentState())->collision(c);
}

unsigned int Game::GetCode(bool state)
{
	SDL_Event event;
	unsigned int code = 0;
	while (state && !exit) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			exit = true;
		else if (event.key.keysym.sym == SDLK_RETURN)
			state = false;
		else if (event.key.type == SDL_KEYDOWN && event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
			code = 10 * code + (event.key.keysym.sym - SDLK_0);
	}
	
	return code;
}

void Game::saveToFile(unsigned int code)
{
	save = true;
	saveCode = code;
}


const unsigned int Game::getRows() const
{
	return ((PlayState*)gameStateMachine->currentState())->getRows();
}

const unsigned int Game::getCols() const
{
	return ((PlayState*)gameStateMachine->currentState())->getCols();
}
void Game::getPacmanPos(unsigned int& x, unsigned int& y) {
	((PlayState*)gameStateMachine->currentState())->getPacmanPos(x, y);
}

void Game::winGame()
{
	win = true;
}

void Game::endGame()
{
	((PlayState*)gameStateMachine->currentState())->endGame();
}

void Game::ghostScared(unsigned int energy)
{
	((PlayState*)gameStateMachine->currentState())->ghostScared(energy);
}

void Game::nextLevel()
{
	((PlayState*)gameStateMachine->currentState())->nextLevel();
}

void Game::increasePoints(unsigned int p)
{
	((PlayState*)gameStateMachine->currentState())->increasePoints(p);
}

void Game::setFilename(string&s)
{
	filename = s;
	load = true;
}

GameStateMachine * Game::getGameStateMachine()
{
	return gameStateMachine;
}

void Game::setExit(bool e)
{
	exit = e;
}

Texture* Game::getTexture(TextureType t) {
	return &textures[(int)t];
}