#pragma once
#include "PacManObject.h"
#include "Texture.h"
#include "checkML.h"
enum Direction {
	Right,
	Down,
	Left,
	Up,
	None
};

class GameCharacter : public PacManObject
{
protected:
	unsigned int x = 0;		//Position X
	unsigned int y = 0;		// Position Y
	unsigned int inix = 0;	//Start Position X
	unsigned int iniy = 0;	//Start Position Y
	Direction dir = None;	//Movement direction
	unsigned int anim = 0;
	unsigned int spriteCol;
	unsigned int startVulTime = 0;

	Texture* texture = nullptr;

	GameCharacter();
	GameCharacter(Game * g);
	//Constructor simple de GameCharacter
	GameCharacter(Game * g, unsigned int col);
	//Constructor completo de un GameCharacter con toda su informacion necesaria
	GameCharacter(Game * g, unsigned int col, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir);

	//Procesa el avance de casilla de un gamecharacter
	void forward();
	//Calcula dónde dibujar el gamecharacter dependiedo del tamaño de las celdas del mapa
	virtual SDL_Rect calcDestRect();

public:
	virtual ~GameCharacter();
	//Render se encarga de el dibujado del gamrCharacter
	virtual void render();
	virtual void update();
	//LoadFromFile sirve para cargar un gamecharacter a través de un archivo
	virtual void loadFromFile(istream &archivo);
	//saveToFile guarda la informacion del gamecharacter en un archivo
	virtual void saveToFile(ostream &archivo);
	//setTexture carga una nueva textura para el gamecharacter
	virtual void setTexture(Texture *t);
	//Die procesa la muerte del personaje
	virtual void die() = 0;
	//Sirve para que se pueda obtener el valor de su posicion x desde fuera de la clase
	int getX();
	//Sirve para que se pueda obtener el valor de su posicion y desde fuera de la clase
	int getY();
	//Sirve para que se pueda obtener el valor de su posicion inicial x desde fuera de la clase
	int getIniX();
	//Sirve para que se pueda obtener el valor de su posicion inicial y desde fuera de la clase
	int getIniY();
	//Sirve para que se pueda obtener el valor de su dirección actual desde fuera de la clase
	Direction getDir();
};

