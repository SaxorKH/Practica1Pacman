#pragma once
#include "GameCharacter.h"

class Game;

using namespace std;

class Pacman : public GameCharacter
{
private:
	Direction dirbuffer = None; //Movement direction buffer
	unsigned int lives = 3; //Numberof remaining lifes
	unsigned int energy = 0;//Remaining energy
	bool hasEnergy = false;

public:
	Pacman();	
	// Constructor b�sico de Pacman.
	Pacman(Game* g);
	virtual ~Pacman();

	// Actualiza la posici�n del Pacman, as� como su energ�a.
	void update();		
	// Pierde una vida y regresa a la posici�n de inicio. Si no posee vidas, se acaba el juego.
	void die();			
	// Actualiza la direcci�n del Pacman recibida por las flechas de direcci�n.
	void bufferUpdate(Direction input);	
	// Habilita el contador de la energ�a del Pacman mientras los fantasmas est�n asustados.
	void startEnergy();					
	// Introduce la energ�a inicial del Pacman.
	void setEnergy(unsigned int en);	
	// Recibe las posiciones inicial y actual, as� como la direcci�n, la energ�a y las vidas actuales de un archivo de
	// guardado.
	void loadFromSavefile(istream &archivo);	
	// Guarda posiciones inicial y actual, direcci�n, energ�a y vidas en el archivo de guardado.
	void saveToFile(ostream &archivo);			
	// Renderiza el Pacman y sus vidas.
	void render();								
};

