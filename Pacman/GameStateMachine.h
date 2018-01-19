#pragma once
#include <stack>
#include "GameState.h"
using namespace std;
class GameStateMachine{
private:
	stack<GameState*> states;

public:
	GameStateMachine();
	~GameStateMachine();

	GameState * currentState();
	void pushState(GameState * state);
	void popState();
};

