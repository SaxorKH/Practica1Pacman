#pragma once
#include "Texture.h"
#include "Game.h"

enum MapCell {
	Empty,
	Wall,
	Food,
	Vitamins
};

class GameMap
{
private:
	Game * game;
	Texture* wall;
	MapCell* map;
	unsigned int rows;
	unsigned int cols;

public:
	GameMap();
	GameMap(unsigned int rows, unsigned int cols, Texture* wall);
	~GameMap();
	const MapCell getCellType(unsigned int row, unsigned int col) const;
	void setCellType(unsigned int row, unsigned int col, MapCell type);
	void render();
	void update();
};

