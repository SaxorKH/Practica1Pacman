#pragma once
#include "SDL.h"
#include <list>
#include "texture.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"

#define TOTAL_TEXTURAS 6
#define FRAME_RATE 150
#define TOTAL_LEVELS 2
#define VUL_TIME 10000
using namespace std;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	unsigned int winWidth = 500;
	unsigned int winHeight = 350;
	unsigned int cellSize = 25;
	unsigned int startTime = 0;
	unsigned int nChar;
	unsigned int rows;
	unsigned int cols;
	unsigned int points = 0;
	unsigned int currentLevel;

	bool exit = false;
	bool inicio = true;
	bool funcional;
	bool saveState = false;
	bool newLevel = true;
	bool loadState = false;
	Texture* textures = nullptr;
	list<GameCharacter*> characters;
	GameMap* gameMap = nullptr;
	const string levelPrefix = "..\\levels\\level";
	// Obtiene las dimensiones del mapa a partir del archivo abierto previamente.
	void getMapDimensions(istream & archivo);	
	// Detecta si un GameCharacter ha tocado otro, y ejecuta las respuestas necesarias.
	void collision(list<GameCharacter*>::iterator ini);		
	// Le pide un código numérico al jugador y guada la partida.
	void SaveState();	
	// Le pide un código numérico al jugador y carga la partida.
	void LoadState();	
	// Lee un código numérico del teclado.
	unsigned int GetCode(bool state);	
	// Destruye el mapa.
	void cleanMap();					
	// Renderiza la interfaz.
	void renderInterface();				
	//Renderiza una letra a partir de una fuente.
	void renderLetter(char l, unsigned int x, unsigned int y);	
	// Ejecuta el menú de inicio.
	void MenuInicio();	
	// Genera o abre el archivo de guardado a partir del código y escribe los datos de la partida.
	void saveToFile(unsigned int code); 
	// Renderiza la partida.
	void render();					
	// Actualiza el estado de la partida.
	void update();						
	// Carga un mapa de acuerdo al nombre de un archivo. Vale tanto un archivo de nivel como uno de guardado.
	bool loadMap(const string& filename, bool savefile = false);	
	// Recibe y gestiona los eventos del juego.
	void handleEvents();		
	// Recibe y gestiona los eventos del menú de inicio.
	void MenuEvents();			


public:
	// Constructor de la clase Game. Inicia SDL y crea el renderer, la ventana y las texturas.
	Game();		
	// Destructor de la clase Game. Destruye el renderer, la ventana y las texturas, así como cierra SDL.
	~Game();	
	// Devuelve un booleano que indica si el Game se ha creado correctamente.
	const bool getFuncional() const;	
	// Devuelve un puntero al renderer.
	SDL_Renderer * getRenderer() const; 
	// Devuelve el tamaño de las celdas.
	const unsigned int getCellSize() const; 
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
	// Finaliza la partida.
	void endGame();		
	// Pone todos los fantasmas en estado "asustado".
	void ghostScared(unsigned int energy = 0);	
	// Avanza al siguiente nivel.
	void nextLevel();	
	// Incrementa la puntuación del jugador en la cantidad dada por el parámetro.
	void increasePoints(unsigned int p);	
};

