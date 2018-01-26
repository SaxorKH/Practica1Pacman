#pragma once
#include "SDL.h"
#include <list>
#include "texture.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"
#include "checkML.h"
#include "GameStateMachine.h"

#define TOTAL_TEXTURAS 10
#define TOTAL_LEVELS 2
#define VUL_TIME 10000
#define FRAME_RATE 150
const string levelPrefix = "..\\levels\\level";
using namespace std;

enum TextureType {
	CharacterTexture,
	WallTexture,
	FoodTexture,
	VitaminTexture,
	FontTexture,
	MainTexture,
	PauseTexture,
	GameOverTexture,
	WinTexture,
	ButtonTexture
};

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine = nullptr;
	string filename;
	Texture * textures = nullptr;

	bool exit = false;
	bool save = false;
	bool win = false;
	unsigned int saveCode;
	bool newLevel = true;
	bool load = false;
	// Lee un código numérico del teclado.
	unsigned int GetCode(bool state);	
	// Renderiza la partida.
	void render();					
	// Actualiza el estado de la partida.
	void update();						
	// Recibe y gestiona los eventos del juego.
	void handleEvents();		


public:
	// Constructor de la clase Game. Inicia SDL y crea el renderer, la ventana y las texturas.
	Game();		
	// Destructor de la clase Game. Destruye el renderer, la ventana y las texturas, así como cierra SDL.
	~Game();
	// Devuelve un puntero al renderer.
	SDL_Renderer * getRenderer() const; 
	// Devuelve un puntero al window
	SDL_Window * getWindow() const;
	// Devuelve el tamaño de las celdas.
	const unsigned int getCellSize() const;

	Texture* getTexture(TextureType t);
	// Cambia el estado del boleano "exit".
	void setExit(bool e);
	// Ejecuta el juego.
	void run();		
	// Lee si se puede avanzar a la celda siguiente a la posición y dirección dadas.
	const bool nextCell(unsigned int x, unsigned int y, Direction dir) const;	
	// Devuelve las filas del mapa.
	const unsigned int getRows() const;		
	// Devuelve las columnas del mapa.
	const unsigned int getCols() const;		
	// Escribe la posición x e y del Pacman en los atributos utilizados.
	void getPacmanPos(unsigned int& x, unsigned int& y);
	void winGame();
	// Finaliza la partida.
	void endGame();		
	// Pone todos los fantasmas en estado "asustado".
	void ghostScared(unsigned int energy = 0);	
	// Avanza al siguiente nivel.
	void nextLevel();	
	// Incrementa la puntuación del jugador en la cantidad dada por el parámetro.
	void increasePoints(unsigned int p);	
	void setFilename(string&s);
	GameStateMachine* getGameStateMachine();

	// Detecta si un GameCharacter ha tocado otro, y ejecuta las respuestas necesarias.
	void collision(GameCharacter&c);
	// Genera o abre el archivo de guardado a partir del código y escribe los datos de la partida.
	void saveToFile(unsigned int code);
};

