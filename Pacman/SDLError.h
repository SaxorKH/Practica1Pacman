#pragma once
#include "PacManError.h"
class SDLError :
	public PacManError
{
public:
	SDLError(string m);
	~SDLError();
};

