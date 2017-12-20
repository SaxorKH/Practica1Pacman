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
		funcional = textures[4].load(renderer, "..\\images\\font.jpg", 10, 10);
		funcional = textures[5].load(renderer, "..\\images\\MenuInicio.png");
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
	MenuInicio();
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
	SDL_RenderClear(renderer);
	renderInterface();
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
	archivo.close();
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

void Game::MenuEvents()
{
	SDL_Event event;
	int x;
	int y;
	while (SDL_PollEvent(&event) && !exit) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			inicio = false;
			break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				if (event.button.button == SDL_BUTTON_LEFT && x >= 64 && x <= 187 && y >= 278 && y <= 328)
					inicio = false;
				break;
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

	winWidth = (cols+7)*cellSize;
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
		else if (event.key.type == SDL_KEYDOWN && event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
			code = 10 * code + (event.key.keysym.sym - SDLK_0);
	}

	if (code == SAVE_CODE)
		saveToFile();
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

void Game::renderInterface()
{
	renderLetter('P', cols + 1, 1);
	renderLetter('u', cols + 2, 1);
	renderLetter('n', cols + 3, 1);
	renderLetter('t', cols + 4, 1);
	renderLetter('o', cols + 5, 1);
	renderLetter('s', cols + 6, 1);
	renderLetter(':', cols + 7, 1);
	list<char> num;
	unsigned int aux = points;
	do {
		num.push_front((aux % 10) + '0');
		aux /= 10;
	} while (aux != 0);
	int n = 1;
	for(list<char>::iterator it = num.begin(); n <= num.size(); it++, n++)
		renderLetter(*it, cols + n, 2);
	renderLetter('V', cols + 1, 3);
	renderLetter('i', cols + 2, 3);
	renderLetter('d', cols + 3, 3);
	renderLetter('a', cols + 4, 3);
	renderLetter('s', cols + 5, 3);
	renderLetter(':', cols + 6, 3);
}

void Game::renderLetter(char l, unsigned int x, unsigned int y)
{
	SDL_Rect dest;
	dest.w = dest.h = cellSize;
	dest.x = x*cellSize;
	dest.y = y*cellSize;
	switch (l) {
	default:
		textures[4].renderFrame(renderer, dest, 9, 9);
		break;
	case 'P':
		textures[4].renderFrame(renderer, dest, 4, 8);
		break;
	case 'u':
		textures[4].renderFrame(renderer, dest, 8, 5);
		break;
	case 'n':
		textures[4].renderFrame(renderer, dest, 7, 8);
		break;
	case 't':
		textures[4].renderFrame(renderer, dest, 8, 4);
		break;
	case 'o':
		textures[4].renderFrame(renderer, dest, 7, 9);
		break;
	case 's':
		textures[4].renderFrame(renderer, dest, 8, 3);
		break;
	case 'V':
		textures[4].renderFrame(renderer, dest, 5, 4);
		break;
	case 'i':
		textures[4].renderFrame(renderer, dest, 7, 3);
		break;
	case 'd':
		textures[4].renderFrame(renderer, dest, 6, 8);
		break;
	case 'a':
		textures[4].renderFrame(renderer, dest, 6, 5);
		break;
	case ':':
		textures[4].renderFrame(renderer, dest, 2, 6);
		break;
	case '0':
		textures[4].renderFrame(renderer, dest, 1, 6);
		break;
	case '1':
		textures[4].renderFrame(renderer, dest, 1, 7);
		break;
	case '2':
		textures[4].renderFrame(renderer, dest, 1, 8);
		break;
	case '3':
		textures[4].renderFrame(renderer, dest, 1, 9);
		break;
	case '4':
		textures[4].renderFrame(renderer, dest, 2, 0);
		break;
	case '5':
		textures[4].renderFrame(renderer, dest, 2, 1);
		break;
	case '6':
		textures[4].renderFrame(renderer, dest, 2, 2);
		break;
	case '7':
		textures[4].renderFrame(renderer, dest, 2, 3);
		break;
	case '8':
		textures[4].renderFrame(renderer, dest, 2, 4);
		break;
	case '9':
		textures[4].renderFrame(renderer, dest, 2, 5);
		break;
	}
}

void Game::MenuInicio()
{
	SDL_Rect destRect;
	destRect.h = winHeight;
	destRect.w = winWidth;
	destRect.x = destRect.y = 0;
	textures[5].render(renderer, destRect);
	SDL_RenderPresent(renderer);
	while (inicio) {
		MenuEvents();
	}
}

void Game::saveToFile()
{
	ofstream archivo;
	archivo.open(levelPrefix + saveName, ios_base::trunc);
	if (archivo.is_open()) {
		archivo << currentLevel << " " << points << endl;
		gameMap->saveToFile(archivo);
		archivo << (characters.size() - 1) << endl;
		for (list<GameCharacter*>::iterator it = ++characters.begin(); it != characters.end(); it++)
			(*it)->saveToFile(archivo);
		characters.front()->saveToFile(archivo);
		archivo.close();
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
