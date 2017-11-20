#include "GameMap.h"
#include "Game.h"


GameMap::GameMap()
{
}

GameMap::GameMap(unsigned int rows, unsigned int cols, Texture * wall, Texture* food, Texture * vitamin, Game * game)
{
	this->wall = wall;
	this->food = food;
	this->vitamin = vitamin;
	this->game = game;
	this->cols = cols;
	this->rows = rows;
	map = new MapCell[rows*cols];
}


GameMap::~GameMap()
{
	delete[] map;
}

const MapCell GameMap::getCellType(unsigned int row, unsigned int col) const
{
		return map[(row%rows)*cols + col%cols];
	return Wall;
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
	if (getCellType(py, px) == Food || getCellType(py, px) == Vitamins) {
		setCellType(py, px, Empty);
		totalFood--;
	}
	if (totalFood == 0)
		game->endGame();


}

const unsigned int GameMap::getRows() const
{
	return rows;
}

const unsigned int GameMap::getCols() const
{
	return cols;
}
