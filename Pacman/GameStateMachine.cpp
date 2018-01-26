#include "GameStateMachine.h"

#include "checkML.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
	while (!states.empty())
		popState();
}

GameState * GameStateMachine::currentState()
{
	if(!states.empty())
		return states.top();
	return nullptr;
}

void GameStateMachine::pushState(GameState * state)
{
	states.push(state);
}

void GameStateMachine::popState()
{
	if (!states.empty()) {
		delete states.top();
		states.pop();
	}
}
