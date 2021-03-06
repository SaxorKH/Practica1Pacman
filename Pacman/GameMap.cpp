#include "GameMap.h"
#include "Game.h"
#include "FileFormatError.h"
#include "checkML.h"

GameMap::GameMap()
{
}
GameMap::GameMap(unsigned int rows, unsigned int cols, Game * game)
	: PacManObject(game)
{
	this->rows = rows;
	this->cols = cols;
	wall = game->getTexture(WallTexture);
	food = game->getTexture(FoodTexture);;
	vitamin = game->getTexture(VitaminTexture);
	map = new MapCell[rows*cols];
}


GameMap::~GameMap()
{
	delete[] map;
}
void GameMap::loadFromFile(istream &archivo)
{
	rows = game->getRows();
	cols = game->getCols();
	unsigned int cellVal;
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			if (archivo.eof())
				throw FileFormatError("N�mero de filas o columnas incorrecto");
			archivo >> cellVal;
			if (cellVal >= 4)
				throw FileFormatError("Formato de celda imposible");
			setCellType(i, j, (MapCell)cellVal);
		}
	}
}
void GameMap::saveToFile(ostream & archivo)
{
	archivo << rows << " " << cols << endl;
	unsigned int cellVal;
	for (unsigned int i = 0; i < rows; i++){
		for (unsigned int j = 0; j < cols; j++) {
			cellVal = getCellType(i, j);
			archivo << (unsigned int) cellVal << " ";
		}
		archivo << endl;
	}
}
const MapCell GameMap::getCellType(unsigned int row, unsigned int col) const
{
	return map[(row%rows)*cols + col%cols];
}
void GameMap::setCellType(unsigned int row, unsigned int col, MapCell type)
{
	if (row < rows && col < cols) {
		map[row*cols + col] = type;
		if (type == Food || type == Vitamins) 
			totalFood++;
	}
}
void GameMap::render()
{
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	destRect.h = destRect.w = cellSize;
	for(unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++) {
			destRect.x = cellSize * j;
			destRect.y = cellSize * i;
			switch (getCellType(i, j)) {
			case Empty:
				break;
			case Wall:
				wall->render(game->getRenderer(), destRect);
				break;
			case Food:
				food->render(game->getRenderer(), destRect);
				break;
			case Vitamins:
				vitamin->render(game->getRenderer(), destRect);
				break;
			}
		}
}
void GameMap::update()
{
	unsigned int px, py;
	game->getPacmanPos(px, py);
	switch (getCellType(py, px)) {
	case Vitamins:
		game->increasePoints(50);
		setCellType(py, px, Empty);
		totalFood--;
		game->ghostScared(); 
		break;
	case Food:
		setCellType(py, px, Empty);
		game->increasePoints(10);
		totalFood--;
		break;
	}
	if (totalFood == 0)
		game->nextLevel();
}
bool GameMap::handleEvent(SDL_Event & e)
{
	return false;
}
const unsigned int GameMap::getRows() const
{
	return rows;
}
const unsigned int GameMap::getCols() const
{
	return cols;
}
