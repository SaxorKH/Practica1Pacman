#include "Game.h"
#include "SmartGhost.h"
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;




Game::Game()
{
	currentLevel = 1;
	srand(time(nullptr));
	characters.push_front(new Pacman(this));
	int winX, winY;	//	Posición	de	la	ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pacman", winX, winY,
		1, 1, SDL_WINDOW_SHOWN);

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
		funcional = textures[4].load(renderer, "..\\images\\font.jpg", 10, 10);
		if (!funcional)
			cout << "Error loading textures\n";
		else {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}
	
}

Game::~Game()
{
	if (textures != nullptr) {
		for (int i = 0; i < TOTAL_TEXTURAS; i++)
			textures[i].~Texture();
		delete[] textures;
	}
	if(gameMap != nullptr)
		delete gameMap;
	while (!characters.empty()) {
		delete characters.back();
		characters.pop_back();
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	while (!exit) {
		if (newLevel) {
			string levelName = levelPrefix;
			char *intStr = new char[2]; 
			sprintf_s(intStr, 2,"%d", currentLevel);
			string str = string(intStr);
			if (currentLevel < 10)
				levelName += "0";
			levelName += str + ".pac";
			cleanMap();
			loadMap(levelName);
		}
			handleEvents();
			update();
			render();
			if (saveState) {
				SaveState();
			}
	}
}

void Game::render()
{
	unsigned int initTime = SDL_GetTicks();
	SDL_RenderClear(renderer);
	gameMap->render();
	for (list<GameCharacter*>::iterator it = characters.begin(); it != characters.end(); it++)
		(*it)->render();
	SDL_RenderPresent(renderer);	//	Muestra	la	escena
}

void Game::update()
{
	unsigned int frameTime = SDL_GetTicks() - startTime;
	if (FRAME_RATE < frameTime) {
		for (list<GameCharacter*>::iterator it = characters.begin(); it != characters.end(); it++){
			(*it)->update();
			collision(it);
		}
		gameMap->update();
		startTime = SDL_GetTicks();
	}
}

bool Game::loadMap(const string & filename, bool savefile)
{
	ifstream archivo;
	archivo.open(filename);

	if (!archivo.is_open())
		return false;
	if (savefile) {
		archivo >> currentLevel;
		archivo >> points;
	}
	getMapDimensions(archivo);
	SDL_SetWindowSize(window, winWidth, winHeight);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	gameMap = new GameMap(rows, cols, &textures[1], &textures[2], &textures[3], this);

	gameMap->loadFromFile(archivo);
	archivo >> nChar;
	for (unsigned int i = 0; i < nChar; i++) {
		int tipo;
		archivo >> tipo;
		if (tipo == 1)
			characters.push_back(new SmartGhost(this, &textures[0]));
		else
			characters.push_back(new Ghost(i%4, this, &textures[0]));
		characters.back()->loadFromFile(archivo);
	}
	Pacman* p =(Pacman*) characters.front();
	p->setTexture(&textures[0]);
	p->loadFromFile(archivo, savefile);
	newLevel = false;
	return true;
}

void Game::handleEvents()
{
	SDL_Event event;
	Pacman * p;
	while (SDL_PollEvent(&event) && !exit) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYDOWN:
			Direction dir;
			switch(event.key.keysym.sym) {
			case SDLK_RIGHT:
				dir = Right;
				break;
			case SDLK_DOWN:
				dir = Down;
				break;
			case SDLK_LEFT:
				dir = Left;
				break;
			case SDLK_UP:
				dir = Up;
				break;
			case SDLK_s:
				saveState = true;
				break;
			}
			p = (Pacman*) characters.front();
			p->bufferUpdate(dir);

		default:
			break;
		}
	}
}

const bool Game::nextCell(unsigned int x, unsigned int y, Direction dir) const
{
	switch (dir) {
	case Right:
		x = (x + 1) % getCols();
		break;
	case Down:
		y = (y + 1) % getRows();
		break;
	case Left:
		if (x == 0)
			x = getCols();
		x--;
		break;
	case Up:
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

void Game::getMapDimensions(istream &archivo) {
	archivo >> rows;
	archivo >> cols;

	winWidth = (cols+4)*cellSize;
	winHeight = rows*cellSize;
}

void Game::collision(list<GameCharacter*>::iterator character)
{
	list<GameCharacter*>::iterator it = characters.begin();
	for (it; it != characters.end(); it++) {
		if (it != character && (*it)->getX() == (*character)->getX() && (*it)->getY() == (*character)->getY()) {
			if (*character == characters.front() || *it == characters.front()) {
				Ghost * aux = nullptr;
				if (*it == characters.front())
					aux = (Ghost*)(*character);
				else if(*character == characters.front())
					aux = (Ghost*)(*it);
				if (aux->getState() == Scared || aux->getState() == Old) {
					aux->die();
					if (aux->getState() == Old) {
						(*it)->~GameCharacter();
						it = characters.erase(it);
						it--;
					}
						
				}
					
				else if (aux->getState() == Alive || aux->getState() == Adult)
					characters.front()->die();
			}
			else{
				Ghost* auxIni = (Ghost*)(*character);
				Ghost* aux = (Ghost*)(*it);
				if (auxIni->getState() == Adult && aux->getState() == Adult && auxIni->getDir() != aux->getDir()) {
					int i = -1;
					bool space = false;
					while (!space && i < 4) {
						i++;
						space = nextCell(aux->getX(), aux->getY(), (Direction)i);
					}
					if (space) {
						characters.push_back(new SmartGhost(this, &textures[0], auxIni->getIniX(), auxIni->getIniY(), aux->getX(), aux->getY(), (Direction)i));
					}
				}
			}
		}
	}
}

void Game::SaveState()
{
	SDL_Event event;
	unsigned int code = 0;
	while (saveState && !exit) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			exit = true;
		else if (event.key.keysym.sym == SDLK_RETURN)
			saveState = false;
		else if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
			code = 10 * code + (event.key.keysym.sym - SDLK_0);
	}

	// implementar guardado
}

void Game::cleanMap()
{
	if (gameMap != nullptr)
		delete gameMap;
	while (characters.size() != 1) {
		delete characters.back();
		characters.pop_back();
	}
}


const unsigned int Game::getRows() const
{
	return rows;
}

const unsigned int Game::getCols() const
{
	return cols;
}
void Game::getPacmanPos(unsigned int& x, unsigned int& y) {
	x = characters.front()->getX();
	y = characters.front()->getY();
}

void Game::endGame()
{
	exit = true;
}

void Game::ghostScared(unsigned int energy)
{
	Pacman* p = (Pacman*)characters.front();
	p->setEnergy(energy);
	for (list<GameCharacter*>::iterator it = ++characters.begin(); it != characters.end(); it++) {
		Ghost * g = (Ghost*)(*it);
		g->scared(energy);
	}
}

void Game::nextLevel()
{
	if (currentLevel == TOTAL_LEVELS)
		endGame();
	else {
		currentLevel++;
		newLevel = true;
	}
}

void Game::increasePoints(unsigned int p)
{
	points += p;
}
