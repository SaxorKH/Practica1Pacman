#include "GameCharacter.h"
#include "Game.h"


GameCharacter::GameCharacter()
{

}

GameCharacter::GameCharacter(Game * g): GameObject(g)
{
}
//Constructor simple de GameCharacter
GameCharacter::GameCharacter(Game * g, Texture * t, unsigned int col) : GameObject(g)
{
	texture = t;
	spriteCol = col;
}
//Constructor completo de un GameCharacter con toda su informacion necesaria
GameCharacter::GameCharacter(Game * g, Texture * t, unsigned int col, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir) : GameObject(g)
{
	texture = t;
	spriteCol = col;
	this->inix = inix;
	this->iniy = iniy;
	this->x = x;
	this->y = y;
	this->dir = dir;
}


GameCharacter::~GameCharacter()
{
}
//Render se encarga de el dibujado del gamrCharacter
void GameCharacter::render()
{
	SDL_Rect destRect = calcDestRect();
	anim = int(((SDL_GetTicks() / FRAME_RATE) % 2));
	Direction auxDir;
	if (dir == None)
		auxDir = Right;
	else auxDir = dir;
	texture->renderFrame(game->getRenderer(), destRect, auxDir, spriteCol * 2 + anim);
}
//LoadFromFile sirve para cargar un gamecharacter a través de un archivo
void GameCharacter::loadFromFile(istream &archivo)
{
	archivo >> x;
	archivo >> y;
	archivo >> inix;
	archivo >> iniy;
	unsigned int aux;
	archivo >> aux;
	dir = (Direction) aux;
}
//saveToFile guarda la informacion del gamecharacter en un archivo
void GameCharacter::saveToFile(ostream&archivo)
{
	archivo << x << " " << y << " " << inix << " " << iniy << " " << (unsigned int)dir << " ";
}
//setTexture carga una nueva textura para el gamecharacter
void GameCharacter::setTexture(Texture * t)
{
	texture = t;
}
//Die procesa la muerte del jugador
void GameCharacter::die()
{
}
//Sirve para que se pueda obtener el valor de su posicion x desde fuera de la clase
int GameCharacter::getX()
{
	return x;
}
//Sirve para que se pueda obtener el valor de su posicion y desde fuera de la clase
int GameCharacter::getY()
{
	return y;
}
//Sirve para que se pueda obtener el valor de su posicion inicial x desde fuera de la clase
int GameCharacter::getIniX()
{
	return inix;
}
//Sirve para que se pueda obtener el valor de su posicion inicial y desde fuera de la clase
int GameCharacter::getIniY()
{
	return iniy;
}
//Procesa el avance de casilla de un gamecharacter
void GameCharacter::forward()
{
	if (dir == 0)
		x = (x + 1) % game->getCols();
	else if (dir == 1)
		y = (y + 1) % game->getRows();
	else if (dir == 2) {
		if (x == 0)
			x = game->getCols();
		x--;
	}
	else if (dir == 3) {
		if (y == 0)
			y = game->getRows();
		y--;
	}
}
//Calcula dónde dibujar el gamecharacter dependiedo de del tamaño de las celdas del mapa
SDL_Rect GameCharacter::calcDestRect()
{
	SDL_Rect destRect;
	unsigned int cellSize = game->getCellSize();
	destRect.w = destRect.h = cellSize;
	destRect.x = x * cellSize;
	destRect.y = y * cellSize;
	return destRect;
}
//Sirve para que se pueda obtener el valor de su dirección actual desde fuera de la clase
Direction GameCharacter::getDir()
{
	return dir;
}
