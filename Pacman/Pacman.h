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
	Pacman();	// Constructor b�sico de Pacman.
	Pacman(Game* g);	// Constructor de Pacman con un puntero a Game.
	virtual ~Pacman();	// Destructor de Pacman.

	void update();		// Actualiza la posici�n del Pacman, as� como su energ�a.
	void die();			// Pierde una vida y regresa a la posici�n de inicio. Si no posee vidas, se acaba el juego.
	void bufferUpdate(Direction input);	// Actualiza la direcci�n del Pacman recibida por las flechas de direcci�n.
	void startEnergy();					// Habilita el contador de la energ�a del Pacman mientras los fantasmas est�n 
										// asustados.
	void setEnergy(unsigned int en);	// Introduce la energ�a inicial del Pacman.
	void loadFromSavefile(istream &archivo);	// Recibe las posiciones inicial y actual, as� como la direcci�n, del 
												// archivo. En caso de ser uno de guardado, tambi�n la energ�a y las
												// vidas actuales.
	void saveToFile(ostream &archivo);			// Guarda posiciones inicial y actual, direcci�n, energ�a y vidas en el
												// archivo de guardado.
	void render();								// Renderiza el Pacman y sus vidas.
};

