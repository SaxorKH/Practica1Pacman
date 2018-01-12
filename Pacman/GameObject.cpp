#include "GameObject.h"
#include "Game.h"


GameObject::GameObject()
{
}
GameObject::GameObject(Game * game)
{
	this->game = game;
}


GameObject::~GameObject()
{
}

void GameObject::render()
{
}

void GameObject::update()
{
}

bool GameObject::handleEvent(SDL_Event & e)
{
	return false;
}
