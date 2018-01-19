#include "Game.h"
#include "SmartGhost.h"
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "PlayState.h"
using namespace std;




Game::Game()
{
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
		funcional = textures[6].load(renderer, "..\\images\\MenuPausa.png");
		funcional = textures[7].load(renderer, "..\\images\\GameOver.png");
		funcional = textures[8].load(renderer, "..\\images\\Victoria.png");
		funcional = textures[9].load(renderer, "..\\images\\Botones.png");
		if (!funcional)
			cout << "Error loading textures\n";
		else {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			gameStateMachine = new GameStateMachine();
			gameStateMachine->pushState(new PlayState(this));
		}
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
		if(inicio)
			MenuInicio();
		if (loadState)
			LoadState();
		else {
			if (newLevel) {
				string levelName = levelPrefix;
				if (currentLevel < 10)
					levelName += "0";
				stringstream ss;
				ss << currentLevel;
				levelName += ss.str() + ".pac";
				cleanMap();
				((PlayState*)gameStateMachine->currentState())->loadMap(levelName);
				newLevel = false;
			}
			handleEvents();
			update();
			if (gameStateMachine->currentState() == nullptr)
				exit = true;
			else
				render();
			if (saveState) {
				SaveState();
			}
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

void Game::MenuEvents()
{
	SDL_Event event;
	int x;
	int y;
	while (SDL_PollEvent(&event) && inicio) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			inicio = false;
			break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				if (event.button.button == SDL_BUTTON_LEFT) {
					if(x >= 64 && x <= 187 && y >= 278 && y <= 328)
						inicio = false;
					else if (x >= 314 && x <= 437 && y >= 278 && y <= 328) {
						inicio = false;
						newLevel = false;
						loadState = true;
					}
				}
		default:
			break;
		}
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

SDL_Window * Game::getWindow() const
{
	return window;
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

void Game::collision(GameCharacter&c)
{
	((PlayState*)gameStateMachine->currentState())->collision(c);
}

void Game::SaveState()
{
	unsigned int code = GetCode(saveState);

	if (code != 0) {
		saveToFile(code);
	}
	saveState = false;
}

void Game::LoadState()
{
	unsigned int code = GetCode(loadState);

	stringstream ss;
	ss << code;
	string filename = levelPrefix + "Save" + ss.str() + ".pac";
	if(!(((PlayState*)gameStateMachine->currentState())->loadMap(filename, true))){
		inicio = true;
		newLevel = true;
	}
	loadState = false;
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

void Game::cleanMap()
{
	if (gameMap != nullptr)
		delete gameMap;
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

void Game::saveToFile(unsigned int code)
{
	ofstream archivo;
	stringstream ss;
	ss << code;
	string levelName = levelPrefix + "Save" + ss.str() + ".pac";

	archivo.open(levelName, ios_base::trunc);
	if (archivo.is_open()) {
		archivo << currentLevel << " " << points << endl;
		gameMap->saveToFile(archivo);
/*		archivo << (characters.size() - 1) << endl;
		for (list<GameCharacter*>::iterator it = ++characters.begin(); it != characters.end(); it++)
			(*it)->saveToFile(archivo);
		characters.front()->saveToFile(archivo);*/
		archivo.close();
	}
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