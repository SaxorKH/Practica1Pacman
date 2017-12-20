#include "GameObject.h"
#include "Game.h"
//Se nombran todos los métodos que tendran los diferentes tipos de GameObjects que serán especificados en cadatipo posteriormente


GameObject::GameObject()
{
}
//Se crea el puntero del GameObject al Game
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

void GameObject::loadFromFile(istream & archivo, bool savefile)
{
}

void GameObject::saveToFile()
{
}
