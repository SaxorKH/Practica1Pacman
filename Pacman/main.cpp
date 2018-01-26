#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include "PacManError.h"
#include "checkML.h"
using namespace std;


int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game * game;
	try {
		game = new Game();
		game->run();
		delete game;
	}
	catch (PacManError()) {
		cout << "Error desconocido" << endl;
	}
	return 0;
}