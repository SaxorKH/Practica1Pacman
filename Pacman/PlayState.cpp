#include "PlayState.h"
#include <fstream>
#include <sstream>
#include "Game.h"
#include "SmartGhost.h"
#include "PauseState.h"
#include <time.h>
using namespace std;


PlayState::PlayState(Game * g) : GameState(g)
{
	srand(time(nullptr));
	stage->push_front(new Pacman(game));
	pacman = (Pacman*) stage->front();
}


PlayState::~PlayState()
{
}


bool PlayState::loadMap(const string & filename, bool savefile)
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
	SDL_SetWindowSize(game->getWindow(), winWidth, winHeight);
	SDL_SetWindowPosition(game->getWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	stage->push_back(new GameMap(rows, cols, game));
	map = (GameMap*)stage->back();

	map->loadFromFile(archivo);
	archivo >> nChar;
	for (unsigned int i = 0; i < nChar; i++) {
		int tipo;
		archivo >> tipo;
		if (tipo == 1)
			stage->push_back(new SmartGhost(game));
		else
			stage->push_back(new Ghost(i % 4, game));
		((PacManObject*) stage->back())->loadFromFile(archivo);
	}
	if (savefile)
		pacman->loadFromSavefile(archivo);
	else
		pacman->loadFromFile(archivo);
	newLevel = false;
	archivo.close();
	return true;
}

void PlayState::handleEvent()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			game->setExit(true);
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				game->getGameStateMachine()->pushState(new PauseState(game));
			else pacman->handleEvent(event);
		}
	}
}

const bool PlayState::nextCell(unsigned int x, unsigned int y, Direction dir) const
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
	
	return map->getCellType(y,x) != Wall;
}


const unsigned int PlayState::getCellSize() const
{
	return cellSize;
}

void PlayState::getMapDimensions(istream &archivo) {
	archivo >> rows;
	archivo >> cols;

	winWidth = (cols + 7)*cellSize;
	winHeight = rows*cellSize;
}

void PlayState::collision(GameCharacter&c)
{
	list<GameObject*>::iterator it = stage->begin();
	for (it; it != stage->end(); it++) {
		if ((*it) != map && (*it) != &c && ((GameCharacter*)(*it))->getX() == c.getX() 
			&& ((GameCharacter*)(*it))->getY() == c.getY()) {
			if (&c == pacman || (*it) == pacman) {
				Ghost * aux;
				if (&c == pacman)
					aux = (Ghost*)(*it);
				else
					aux = (Ghost*)&c;
				if (aux->getState() == Scared || aux->getState() == Old) {
					aux->die();
					if (aux->getState() == Old) {
						(*it)->~GameObject();
						it = stage->erase(it);
						it--;
					}

				}

				else if (aux->getState() != Dead)
					pacman->die();
			}
			else {
				Ghost* auxIni = (Ghost*)&c;
				Ghost* aux = (Ghost*)(*it);
				if (auxIni->getState() == Adult && aux->getState() == Adult && auxIni->getDir() != aux->getDir()) {
					int i = -1;
					bool space = false;
					while (!space && i < 4) {
						i++;
						space = this->nextCell(aux->getX(), aux->getY(), (Direction)i);
					}
					if (space) {
						stage->push_back(new SmartGhost(game, auxIni->getIniX(), auxIni->getIniY(), aux->getX(), aux->getY(), (Direction)i));
					}
				}
			}
		}
	}
}

void PlayState::render()
{
	GameState::render();
	renderInterface();
}

void PlayState::SaveState()
{
	unsigned int code = GetCode(saveState);

	if (code != 0) {
		saveToFile(code);
	}
	saveState = false;
}

void PlayState::LoadState()
{
//	unsigned int code = GetCode(loadState);

	stringstream ss;
//	ss << code;
	string filename = levelPrefix + "Save" + ss.str() + ".pac";
	if (!loadMap(filename, true)) {
		inicio = true;
		newLevel = true;
	}
//	loadState = false;
}

unsigned int PlayState::GetCode(bool state)
{
	SDL_Event event;
	unsigned int code = 0;
	while (state) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT) {
			game->setExit(true);
			state = false;
		}
		else if (event.key.keysym.sym == SDLK_RETURN)
			state = false;
		else if (event.key.type == SDL_KEYDOWN && event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
			code = 10 * code + (event.key.keysym.sym - SDLK_0);
	}

	return code;
}

void PlayState::cleanMap()
{
	while (stage->size() != 1) {
		if (stage->back() != nullptr)
			delete stage->back();
		stage->pop_back();
	}
}

void PlayState::renderInterface()
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
	for (list<char>::iterator it = num.begin(); n <= num.size(); it++, n++)
		renderLetter(*it, cols + n, 2);
	renderLetter('V', cols + 1, 3);
	renderLetter('i', cols + 2, 3);
	renderLetter('d', cols + 3, 3);
	renderLetter('a', cols + 4, 3);
	renderLetter('s', cols + 5, 3);
	renderLetter(':', cols + 6, 3);
}

void PlayState::renderLetter(char l, unsigned int x, unsigned int y)
{
	Texture * t = game->getTexture(FontTexture);
	SDL_Rect dest;
	dest.w = dest.h = cellSize;
	dest.x = x*cellSize;
	dest.y = y*cellSize;
	switch (l) {
	default:
		t->renderFrame(game->getRenderer(), dest, 9, 9);
		break;
	case 'P':
		t->renderFrame(game->getRenderer(), dest, 4, 8);
		break;
	case 'u':
		t->renderFrame(game->getRenderer(), dest, 8, 5);
		break;
	case 'n':
		t->renderFrame(game->getRenderer(), dest, 7, 8);
		break;
	case 't':
		t->renderFrame(game->getRenderer(), dest, 8, 4);
		break;
	case 'o':
		t->renderFrame(game->getRenderer(), dest, 7, 9);
		break;
	case 's':
		t->renderFrame(game->getRenderer(), dest, 8, 3);
		break;
	case 'V':
		t->renderFrame(game->getRenderer(), dest, 5, 4);
		break;
	case 'i':
		t->renderFrame(game->getRenderer(), dest, 7, 3);
		break;
	case 'd':
		t->renderFrame(game->getRenderer(), dest, 6, 8);
		break;
	case 'a':
		t->renderFrame(game->getRenderer(), dest, 6, 5);
		break;
	case ':':
		t->renderFrame(game->getRenderer(), dest, 2, 6);
		break;
	case '0':
		t->renderFrame(game->getRenderer(), dest, 1, 6);
		break;
	case '1':
		t->renderFrame(game->getRenderer(), dest, 1, 7);
		break;
	case '2':
		t->renderFrame(game->getRenderer(), dest, 1, 8);
		break;
	case '3':
		t->renderFrame(game->getRenderer(), dest, 1, 9);
		break;
	case '4':
		t->renderFrame(game->getRenderer(), dest, 2, 0);
		break;
	case '5':
		t->renderFrame(game->getRenderer(), dest, 2, 1);
		break;
	case '6':
		t->renderFrame(game->getRenderer(), dest, 2, 2);
		break;
	case '7':
		t->renderFrame(game->getRenderer(), dest, 2, 3);
		break;
	case '8':
		t->renderFrame(game->getRenderer(), dest, 2, 4);
		break;
	case '9':
		t->renderFrame(game->getRenderer(), dest, 2, 5);
		break;
	}
}

void PlayState::saveToFile(unsigned int code)
{
	ofstream archivo;
	stringstream ss;
	ss << code;
	string levelName = levelPrefix + "Save" + ss.str() + ".pac";

	archivo.open(levelName, ios_base::trunc);
	if (archivo.is_open()) {
		archivo << currentLevel << " " << points << endl;
		((PacManObject*)(*(stage->begin()++)))->saveToFile(archivo);
		archivo << (stage->size() - 1) << endl; 
		list<GameObject*>::iterator it = ++stage->begin();
		it++;
		for (it; it != stage->end(); it++)
			((PacManObject*)(*it))->saveToFile(archivo);
		pacman->saveToFile(archivo);
		archivo.close();
	}
}


const unsigned int PlayState::getRows() const
{
	return rows;
}

const unsigned int PlayState::getCols() const
{
	return cols;
}
void PlayState::getPacmanPos(unsigned int& x, unsigned int& y) {
	x = pacman->getX();
	y = pacman->getY();
}

void PlayState::endGame()
{
	end = true;
}

void PlayState::ghostScared(unsigned int energy)
{
	pacman->setEnergy(energy); 
	list<GameObject*>::iterator it = stage->begin();
		it++;
		it++;
	for (; it != stage->end(); it++) {
		Ghost * g = (Ghost*)(*it);
		g->scared(energy);
	}
}

void PlayState::nextLevel()
{
	if (currentLevel == TOTAL_LEVELS)
		endGame();
	else {
		currentLevel++;
		newLevel = true;
	}
}

void PlayState::increasePoints(unsigned int p)
{
	points += p;
}

void PlayState::update() {
	unsigned int frameTime = SDL_GetTicks() - startTime;
	if (!end & newLevel) {
		string levelName = levelPrefix;
		if (currentLevel < 10)
			levelName += "0";
		stringstream ss;
		ss << currentLevel;
		levelName += ss.str() + ".pac";
		cleanMap();
		loadMap(levelName);
		newLevel = false;
	}
	else if (FRAME_RATE < frameTime) {
		GameState::update();
		startTime = SDL_GetTicks();
	}
}

void PlayState::loadSaveFile(string&s) {
	loadMap(s, true);
	newLevel = false;
}
