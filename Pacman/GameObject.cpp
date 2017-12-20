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

void GameObject::loadFromFile(istream & archivo)
{
}

void GameObject::saveToFile(ostream & archivo)
{
}
