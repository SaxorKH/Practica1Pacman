#include "GameObject.h"
#include "Game.h"
#include "checkML.h"


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
