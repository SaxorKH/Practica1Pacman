#include "GameMap.h"



GameMap::GameMap()
{
}

GameMap::GameMap(unsigned int rows, unsigned int cols, Texture * wall)
{
	this->wall = wall;
	map = new MapCell[rows*cols];
}


GameMap::~GameMap()
{
	delete[] map;
}

const MapCell GameMap::getCellType(unsigned int row, unsigned int col) const
{
	if(row < rows && col < cols)
		return map[row*cols + col];
	return Wall;
}

void GameMap::setCellType(unsigned int row, unsigned int col, MapCell type)
{
	if (row < rows && col < cols)
		map[row*cols + col] = type;
}

void GameMap::render()
{
	SDL_Rect destRect;
	destRect.h = destRect.y = 128;
	for(int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			unsigned int cellSize = game->getCellSize();
			destRect.x = cellSize * j;
			destRect.y = cellSize * i;
			switch (getCellType(i, j)) {
			case Empty:
				break;
			case Wall:
				wall->render(game->getRenderer(), destRect);
				break;
			case Food:
				break;
			case Vitamins:
				break;
			}
		}
}

void GameMap::update()
{
}
