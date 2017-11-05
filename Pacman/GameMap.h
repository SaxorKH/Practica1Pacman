#pragma once

class GameMap
{

public:
	enum MapCell {
		Empty,
		Wall,
		Food,
		Vitamins
	};
private:
	MapCell* puntero;
public:
	GameMap(
	puntero = new MapCell[2]();
	~GameMap();


	
};

